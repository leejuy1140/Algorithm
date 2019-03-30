#include <stdio.h>
#include <string.h>
#include <queue>
using namespace std;

const int MAX = 51;

bool visited[MAX][MAX];
int n, m, map[MAX][MAX]; // За, ї­
int dir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

struct INFO
{
	int r, c, dist;
	void setInfo(int _r, int _c, int _d)
	{ r = _r; c = _c; dist = _d; }
};

int bfs(int r, int c)
{
	INFO start;
	start.setInfo(r, c, 0);

	queue<INFO> q;
	q.push(start);
	visited[r][c] = 1;

	INFO cur;
	while (!q.empty())
	{
		cur = q.front();
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			INFO next;
			next.setInfo(cur.r + dir[i][0], cur.c + dir[i][1], cur.dist + 1);
			if (next.r < 0 || next.c < 0 || next.r >= n || next.c >= m) continue;
			if (map[next.r][next.c] == 'W' || visited[next.r][next.c]) continue;

			q.push(next);
			visited[next.r][next.c] = 1;
		}
	}
	return cur.dist;
}


int main()
{
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++)
	{
		getchar();
		for (int j = 0; j < m; j++)
			scanf("%1c", &map[i][j]);
	}
	
	int answer = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (map[i][j] == 'L')
			{
				for (int i = 0; i < n; i++)
					memset(&visited[i], 0, m);

				int dist = bfs(i, j);
				if (dist > answer) answer = dist;
			}
		}
	}
	printf("%d\n", answer);

	return 0;
}