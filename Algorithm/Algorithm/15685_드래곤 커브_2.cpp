#include <stdio.h>
#include <vector>
using namespace std;

const int MAX = 101;

vector<int> dragon; // �巡��Ŀ���� ���� ����.
int n, map[MAX][MAX];
int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, -1, 0, 1 }; // -�ϸ�, �ð���� 90��.

int main()
{
	scanf("%d", &n);
	while (n--)
	{
		int x, y, d, g;
		scanf("%d %d %d %d", &x, &y, &d, &g);

		// 0���� �巡�� Ŀ��.
		map[y][x] = 1;
		x += dx[d];
		y += dy[d];
		map[y][x] = 1;
		dragon.push_back(d);

		// ���� ����.
		if (d % 2) { for (int i = 0; i < 4; i++) dx[i] *= -1; }
		else	   { for (int i = 0; i < 4; i++) dy[i] *= -1; }

		// 1 ~ n���� �巡�� Ŀ��.
		for (int i = 1; i <= g; i++)
		{
			int k = dragon.size() - 1;
			for (k; k >= 0; k--)
			{
				// ���� ���� +90�� ȸ���� ����.
				int prev_d = dragon[k];
				int cur_d = prev_d - 1;
				if (cur_d < 0) cur_d = 3;

				// �ش� �������� �̵�.
				x += dx[cur_d];
				y += dy[cur_d];
				map[y][x] = 1;
				dragon.push_back(cur_d);
			}
		}

		// ���� ����.
		if (d % 2) { for (int i = 0; i < 4; i++) dx[i] *= -1; }
		else	   { for (int i = 0; i < 4; i++) dy[i] *= -1; }
		dragon.clear();
	}

	// ������ ���� �巡�� Ŀ���� ���� ���� ī����.
	int answer = 0;
	for (int i = 0; i < MAX - 1; i++)
	{
		for (int j = 0; j < MAX - 1; j++)
			if (map[i][j] && map[i + 1][j] && map[i][j + 1] && map[i + 1][j + 1])
				answer++;
	}
	printf("%d", answer);
	return 0;
}