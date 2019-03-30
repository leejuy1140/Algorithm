#include <stdio.h>
#include <string.h>

const int MAP_MAX = 15;
const int PATH_MAX = 205;

bool visited[PATH_MAX];
int n, m, map[MAP_MAX][MAP_MAX]; // 행, 열
int dir[2][2] = { {0, 1}, {1, 0} }; // 행, 열

int pathCnt, pathMax;
void commute(int r, int c, int pathSum)
{
	if (r == n && c == m)
	{
		pathCnt++;
		if (pathSum > pathMax) pathMax = pathSum;
		return;
	}

	for (int i = 0; i < 2; i++)
	{
		int nr = r + dir[i][0];
		int nc = c + dir[i][1];
		if (nr < 1 || nc < 1 || nr > n || nc > m) continue;
		if (visited[map[nr][nc]]) continue;

		visited[map[nr][nc]] = 1;
		commute(nr, nc, pathSum + map[nr][nc]);
		visited[map[nr][nc]] = 0;
	}
}

int main()
{
	int t;
	scanf("%d", &t);
	for (int tt = 1; tt <= t; tt++)
	{
		scanf("%d %d", &n, &m);
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				scanf("%d", &map[i][j]);

		visited[map[1][1]] = 1;
		commute(1, 1, map[1][1]);

		if (!pathCnt) pathMax = -1;
		printf("#%d %d %d\n", tt, pathCnt, pathMax);

		pathCnt = pathMax = 0;
		memset(visited, 0, PATH_MAX);
	}
	return 0;
}