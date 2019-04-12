#include <stdio.h>
#include <vector>	 // 나무 관리.
#include <algorithm> // 나무 나이 정렬.
using namespace std;

const int MAX = 11;
const int DEAD = 9999999;

vector<int> tree[MAX][MAX]; // (r, c)의 나무 정보.
int n, m, k, A[MAX][MAX], map[MAX][MAX]; // (r, c)의 양분.
int dr[8] = { 0, 0, 1, -1, 1, 1, -1, -1 };
int dc[8] = { 1, -1, 0, 0, -1, 1, -1, 1 };

void Spring()
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			// 나무가 여러개면, 정렬 (어린 나무부터 양분 먹기 위해)
			if (tree[i][j].size() > 1)
				sort(tree[i][j].begin(), tree[i][j].end());

			// 어린 나무부터 양분 먹고 나이먹기 시작.
			for (int t = 0; t < tree[i][j].size(); t++)
			{
				// 양분이 충분하면, 양분을 나이만큼 먹고 나이 + 1.
				if (tree[i][j][t] <= map[i][j])
				{
					map[i][j] -= tree[i][j][t];
					tree[i][j][t]++;
				}

				// 충분하지 않으면, 현재 나이에 -1을 곱해서 죽음 표시.
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
			// 죽은 나무 나이의 절반을 양분으로 추가.
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
			// 나이가 5배수인 나무의 인접 8칸에 나이가 1인 나무 번식.
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
	// 모든 칸에 A만큼의 양분 추가.
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
	int answer = 0; // 나무 개수 구하기.
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			answer += tree[i][j].size();
	printf("%d", answer);

	return 0;
}