#include <stdio.h>
#include <vector>	 // ���� ����.
#include <algorithm> // ���� ���� ����.
using namespace std;

const int MAX = 11;
const int DEAD = 9999999;

vector<int> tree[MAX][MAX]; // (r, c)�� ���� ����.
int n, m, k, A[MAX][MAX], map[MAX][MAX]; // (r, c)�� ���.
int dr[8] = { 0, 0, 1, -1, 1, 1, -1, -1 };
int dc[8] = { 1, -1, 0, 0, -1, 1, -1, 1 };

void Spring()
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			// ������ ��������, ���� (� �������� ��� �Ա� ����)
			if (tree[i][j].size() > 1)
				sort(tree[i][j].begin(), tree[i][j].end());

			// � �������� ��� �԰� ���̸Ա� ����.
			for (int t = 0; t < tree[i][j].size(); t++)
			{
				// ����� ����ϸ�, ����� ���̸�ŭ �԰� ���� + 1.
				if (tree[i][j][t] <= map[i][j])
				{
					map[i][j] -= tree[i][j][t];
					tree[i][j][t]++;
				}

				// ������� ������, ���� ���̿� -1�� ���ؼ� ���� ǥ��.
				else tree[i][j][t] *= -1;
			}
		}
	}
}

void Summer()
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			// ���� ���� ������ ������ ������� �߰�.
			for (int t = 0; t < tree[i][j].size(); t++)
			{
				if (tree[i][j][t] < 0)
				{
					map[i][j] += ((tree[i][j][t] * -1) / 2);
					tree[i][j].erase(tree[i][j].begin() + t);
					t--;
				}
			}
		}
	}
}

void Fall()
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			// ���̰� 5����� ������ ���� 8ĭ�� ���̰� 1�� ���� ����.
			for (int t = 0; t < tree[i][j].size(); t++)
			{
				if (tree[i][j][t] % 5 == 0)
				{
					for (int d = 0; d < 8; d++)
					{
						int ii = i + dr[d];
						int jj = j + dc[d];
						if (ii < 1 || jj < 1 || ii > n || jj > n) continue;
						tree[ii][jj].push_back(1);
					}
				}
			}
			map[i][j] += A[i][j];
		}
	}
}

void Winter()
{
	// ��� ĭ�� A��ŭ�� ��� �߰�.
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			map[i][j] += A[i][j];
}

int main()
{
	scanf("%d %d %d", &n, &m, &k);
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			map[i][j] = 5;
			scanf("%d", &A[i][j]);
		}
	}
	for (int i = 0; i < m; i++)
	{
		int x, y, z;
		scanf("%d %d %d", &x, &y, &z);
		tree[x][y].push_back(z);
	}

	while (k--)
	{
		Spring();
		Summer();
		Fall();
	}
	int answer = 0; // ���� ���� ���ϱ�.
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			answer += tree[i][j].size();
	printf("%d", answer);

	return 0;
}