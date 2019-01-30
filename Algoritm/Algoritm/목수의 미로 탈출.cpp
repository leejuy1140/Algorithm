#include <stdio.h>
#include <queue>
using namespace std;

const int MAX = 1001;

int n, m, map[MAX][MAX], visited[MAX][MAX]; // 행, 열
int dir[4][2] = { {-1, 0}, {0, 1}, {0, -1}, {1, 0} }; // 북동서남
struct INFO
{
	int r, c, cnt, ax;

	void setInfo(int _r, int _c, int _cnt, int _ax)
	{ r = _r; c = _c; cnt = _cnt; ax = _ax; }
};

int bfs(INFO first)
{
	queue<INFO> q;
	q.push(first);
	visited[first.r][first.c] = 1;

	while (!q.empty())
	{
		INFO cur = q.front();
		q.pop();

		if (cur.r == n - 1 && cur.c == m - 1) return cur.cnt;

		for (int i = 0; i < 4; i++)
		{
			INFO next;
			next.setInfo(cur.r + dir[i][0], cur.c + dir[i][1], cur.cnt + 1, cur.ax);
			
			if (next.r < 0 || next.c < 0 || next.r >= n || next.c >= m) continue;
			if (visited[next.r][next.c] == 1) continue;

			// 벽을 부수고 지나간 길을 이미 벽을 부순 애들이 지나가지 못하도록
			// 중복 push 되는 것 방지 !!!
			if (visited[next.r][next.c] == 2 && !next.ax) continue;

			if (map[next.r][next.c] && next.ax)
			{
				next.ax = 0;
				q.push(next);

				// 여기서 부순 길이 최적의 길이 아님에도 불구하고, 발자취를 표시해놔,
				// 다른 최적의 길이 지나가지 못할 수 있으므로, 2로 다르게 표시 !
				visited[next.r][next.c] = 2;
			}
			if (!map[next.r][next.c])
			{
				q.push(next);

				// 벽을 부수고 지나간 길은 2로 표시해,
				// 벽을 아직 부수지 않을 애가 지나갈 수 있도록 !!!
				if (!next.ax) visited[next.r][next.c] = 2;
				else	  	  visited[next.r][next.c] = 1;
			}
		}
	}
	return -1;
}

int main()
{
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			scanf("%1d", &map[i][j]);

	INFO start;
	start.setInfo(0, 0, 1, 1);
	printf("%d", bfs(start));

	return 0;
}