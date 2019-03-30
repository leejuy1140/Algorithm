#include <stdio.h>
#include <queue>
using namespace std;

const int SIZE = 1001;
const int MAX = 999999999;

int n, m, map[SIZE][SIZE]; // За, ї­
bool visited[SIZE][SIZE];
struct INFO { int r, c, dist; };
int dir[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

int bfs(int _r, int _c, int _dist)
{
	INFO start;
	start.r = _r;
	start.c = _c;
	start.dist = _dist;

	queue<INFO> q;
	q.push(start);
	visited[start.r][start.c] = 1;

	int minDist = MAX;
	while (!q.empty())
	{
		INFO cur = q.front();
		q.pop();

		if (cur.r == 0 && cur.c == m - 1)
		{
			minDist = minDist < cur.dist ? minDist : cur.dist;
			continue;
		}

		for (int i = 0; i < 4; i++)
		{
			INFO next;
			next.r = cur.r + dir[i][0];
			next.c = cur.c + dir[i][1];
			next.dist = cur.dist + 1;

			if (next.r < 0 || next.c < 0) continue;
			if (next.r >= n || next.c >= m) continue;
			if (map[next.r][next.c]) continue;
			if (visited[next.r][next.c]) continue;

			q.push(next);
			visited[next.r][next.c] = 1;
		}
	}
	return minDist;
}

int main()
{
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			scanf("%d", &map[i][j]);
	printf("%d", bfs(n - 1, 0, 0));
	return 0;
}