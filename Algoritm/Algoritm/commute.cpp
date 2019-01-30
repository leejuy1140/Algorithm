#include <stdio.h>
#include <string.h>

const int NUM_MAX = 201;
const int MAP_MAX = 15;

int n, m, map[MAP_MAX][MAP_MAX];
bool chk[NUM_MAX]; // 칸에 적혀있는 수 체크
int direction[2][2] = { {1, 0}, {0, 1} }; // 오른쪽, 아래
int pathCnt = 0, maxPathSum = 0;

void commute(int x, int y, int sum)
{
	if (x == m - 1 && y == n - 1)
	{
		if (maxPathSum < sum) maxPathSum = sum;
		pathCnt++;
		return;
	}

	for (int dir = 0; dir < 2; dir++)
	{
		int new_x = x + direction[dir][0];
		int new_y = y + direction[dir][1];
		if (new_x < 0 || new_y < 0 || new_x >= m || new_y >= n) continue;

		int new_path = map[new_y][new_x];
		if (chk[new_path]) continue;

		chk[new_path] = 1;
		commute(new_x, new_y, sum + new_path);
		chk[new_path] = 0;
	}
	return;
}

int main()
{
	int T; scanf("%d", &T);
	for (int t = 1; t <= T; t++)
	{
		scanf("%d %d", &n, &m);
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
				scanf("%d", &map[i][j]);
		}

		chk[map[0][0]] = 1;
		commute(0, 0, map[0][0]);

		if (!pathCnt) maxPathSum = -1;
		printf("#%d %d %d\n", t, pathCnt, maxPathSum);
		
		memset(chk, 0, NUM_MAX);
		pathCnt = 0; maxPathSum = 0;
	}

	return 0;
}