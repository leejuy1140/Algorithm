#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

const int MAX = 51;

bool visited[MAX][MAX];
int w, h, map[MAX][MAX];
int dr[8] = { 0, 0, -1, 1, 1, 1, -1, -1 };
int dc[8] = { -1, 1, 0, 0, -1, 1, -1, 1 };

int FindIsland(int r, int c)
{
	queue<pair<int, int>> q;
	q.push(make_pair(r, c));
	visited[r][c] = true;

	while (!q.empty())
	{
		pair<int, int> cur = q.front();
		q.pop();

		for (int i = 0; i < 8; i++)
		{
			int nr = cur.first + dr[i];
			int nc = cur.second + dc[i];
			if (nr < 0 || nc < 0 || nr >= h || nc >= w) continue;
			if (!map[nr][nc] || visited[nr][nc]) continue;

			q.push(make_pair(nr, nc));
			visited[nr][nc] = true;
		}
	}
	return 1;
}

int main()
{
	while (1)
	{
		scanf("%d %d", &w, &h);
		if (!w && !h) break;

		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++)
				scanf("%d", &map[i][j]);

		int answer = 0;
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++)
				if (map[i][j] && !visited[i][j])
					answer += FindIsland(i, j);
		printf("%d\n", answer);

		memset(visited, false, sizeof(visited));
	}
	return 0;
}