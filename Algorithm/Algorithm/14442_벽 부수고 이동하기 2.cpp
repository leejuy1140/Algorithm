#include <iostream>
#include <queue>
using namespace std;

const int MAX = 1005;
const int K_MAX = 11;

int n, m, k, map[MAX][MAX];
bool visited[MAX][MAX][K_MAX]; // 벽을 부순 개수로 체크.
int dir[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
struct Info { int r, c, wall, dist; };

/* (1, 1) ~ (n, m)까지 최단 거리 확인. */
int bfs()
{
	queue<Info> q;
	q.push({ 1, 1, 0, 1 });
	visited[1][1][0] = true;

	while (!q.empty())
	{
		Info cur = q.front();
		q.pop();

		// (n, m)에 도착했으면, 거리 반환.
		if (cur.r == n && cur.c == m) return cur.dist;

		for (int i = 0; i < 4; i++)
		{
			int nr = cur.r + dir[i][0];
			int nc = cur.c + dir[i][1];
			if (nr < 1 || nc < 1 || nr > n || nc > m) continue;

			if (map[nr][nc]) // 벽
			{
				if (cur.wall + 1 <= k) // 부술 수 있다면, 부숨.
				{
					if (visited[nr][nc][cur.wall + 1]) continue;
					q.push({ nr, nc, cur.wall + 1, cur.dist + 1 });
					visited[nr][nc][cur.wall + 1] = true;
				}
				else continue;
			}
			else // 벽이 아니므로 계속 탐색.
			{
				if (visited[nr][nc][cur.wall]) continue;
				q.push({ nr, nc, cur.wall, cur.dist + 1 });
				visited[nr][nc][cur.wall] = true;
			}
		}
	}
	return -1;
}

int main()
{
	scanf("%d %d %d", &n, &m, &k);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf("%1d", &map[i][j]);
	printf("%d", bfs());
	return 0;
}