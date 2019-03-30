#include <stdio.h>
#include <queue>
using namespace std;

const int MAX = 101;
enum { EMPTY = -1, TOMATO, RIPE };

bool visited[MAX][MAX][MAX];
int n, m, h, map[MAX][MAX][MAX]; // 행, 열, 높이
int dir[6][3] = { {0, 0, -1}, {0, 0, 1}, {-1, 0, 0}, {1, 0, 0}, {0, -1, 0}, {0, 1, 0} };

struct INFO
{
	int r, c, z, day;
	void SetInfo(int _r, int _c, int _z, int _day)
	{ r = _r; c = _c; z = _z; day = _day; }
};

int bfs(queue<INFO> &q, int haveToRipe)
{
	while (!q.empty())
	{
		INFO cur = q.front();
		q.pop();

		for (int i = 0; i < 6; i++)
		{
			INFO next;
			next.SetInfo(cur.r + dir[i][0], cur.c + dir[i][1], cur.z + dir[i][2], cur.day + 1);
			
			if (next.r < 0 || next.c < 0 || next.z < 0) continue;
			if (next.r >= n || next.c >= m || next.z >= h) continue;

			if (map[next.r][next.c][next.z] == TOMATO && !visited[next.r][next.c][next.z])
			{
				haveToRipe--;
				q.push(next);
				visited[next.r][next.c][next.z] = 1;
				if (!haveToRipe) return next.day;
			}
		}
	}
	return -1;
}

int main()
{
	queue<INFO> q;
	int notRiped = 0;

	scanf("%d %d %d", &m, &n, &h);
	for (int k = 0; k < h; k++)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				scanf("%d", &map[i][j][k]);
				if (map[i][j][k] == TOMATO) notRiped++;
				if (map[i][j][k] == RIPE && !visited[i][j][k])
				{
					INFO start;
					start.SetInfo(i, j, k, 0);
					q.push(start);
					visited[i][j][k] = 1;
				}
			}
		}
	}
	if (!notRiped) printf("0\n");
	else		   printf("%d\n", bfs(q, notRiped));

	return 0;
}