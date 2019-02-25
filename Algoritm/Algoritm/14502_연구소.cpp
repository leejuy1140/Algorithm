#include <stdio.h>
#include <string.h>
#include <queue>
using namespace std;

const int MAX = 10;
enum { EMPTY = 0, WALL, VIRUS, MYWALL };

bool visited[MAX][MAX];
vector<pair<int, int>> virus;
int n, m, emptyArea, maxArea, map[MAX][MAX];
int dir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

/* 안전 영역의 크기 반환. */
int bfs()
{
	for (int i = 1; i <= n; i++)
		memset(&visited[i], 0, m + 1);

	queue<pair<int, int>> q;
	for (int i = 0; i < virus.size(); i++) q.push(virus[i]);

	int curArea = emptyArea - 3;
	while (!q.empty())
	{
		pair<int, int> cur = q.front();
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			int nr = cur.first + dir[i][0];
			int nc = cur.second + dir[i][1];
			if (nr < 1 || nc < 1 || nr > n || nc > m) continue;
			if (map[nr][nc] != EMPTY || visited[nr][nc]) continue;

			curArea--;
			q.push(make_pair(nr, nc));
			visited[nr][nc] = 1;
		}
	}
	return curArea;
}

/* 빈 지역에 벽을 세우고, 3개가 되면, 안전 영역을 구함. */
void dfs(int r, int c, int wallCnt)
{
	if (wallCnt == 3)
	{
		int curArea = bfs();
		if (curArea > maxArea) maxArea = curArea;
		return;
	}

	int i = r, j = c + 1;
	if (j > m) { i++; j = 1; }
	for (i; i <= n; i++)
	{
		for (j; j <= m; j++)
		{
			if (map[i][j] == EMPTY)
			{
				map[i][j] = MYWALL;
				dfs(i, j, wallCnt + 1);
				map[i][j] = EMPTY;
			}
		}
		j = 1;
	}
}

int main()
{
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			scanf("%d", &map[i][j]);
			if (map[i][j] == EMPTY) emptyArea++;
			if (map[i][j] == VIRUS) virus.push_back(make_pair(i, j));
		}
	}

	/* 비어있는 곳부터 1번째  벽 세우기. */
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (map[i][j] == EMPTY)
			{
				map[i][j] = MYWALL;
				dfs(i, j, 1);
				map[i][j] = EMPTY;
			}
		}
	}
	printf("%d\n", maxArea);

	return 0;
}