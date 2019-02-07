#include <stdio.h>
#include <queue>
using namespace std;

const int MAX = 101;
const int BUILDING = 100000;

bool visited[MAX][MAX];
int n, x, y, k, map[MAX][MAX];
int dir[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

struct INFO
{
	int r, c, time;
	void setInfo(int _r, int _c, int _t)
	{ r = _r; c = _c; time = _t; }
};

int bfs(int c, int r)
{
	INFO start;
	start.setInfo(r, c, 0);

	queue<INFO> q;
	q.push(start);
	visited[r][c] = 1;

	int damCnt = 0;
	while (!q.empty())
	{
		INFO cur = q.front();
		q.pop();

		if (cur.time == k) damCnt++;

		for (int i = 0; i < 4; i++)
		{
			INFO next;
			next.setInfo(cur.r + dir[i][0], cur.c + dir[i][1], cur.time + 1);
			if (next.r < 0 || next.c < 0 || next.r >= n || next.c >= n) continue;
			if (map[next.r][next.c] == BUILDING || visited[next.r][next.c]) continue;

			q.push(next);
			visited[next.r][next.c] = 1;
		}
	}
	if (!damCnt) return -1;
	else	    	 return damCnt;
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			scanf("%d", &map[i][j]);
			if (map[i][j]) map[i][j] = BUILDING;
		}
	}
	scanf("%d %d\n%d", &x, &y, &k);

	int answer = bfs(x - 1, y - 1);
	printf("%d\n", answer);

	return 0;
}