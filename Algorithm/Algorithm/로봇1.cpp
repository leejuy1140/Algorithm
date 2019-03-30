#include <stdio.h>
#include <queue>
using namespace std;

#define SIZE 105

bool visited[SIZE][SIZE][5]; // dir
int n, m, map[SIZE][SIZE];
int dir[5][2] = { {0, 0}, {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

struct ROBOT { int r, c, dir, cnt; };
ROBOT start, dest;

int bfs() {
	queue<ROBOT> q;
	q.push(start);

	while (!q.empty()) {
		ROBOT cur = q.front(); q.pop();
		if (cur.r == dest.r && cur.c == dest.c && cur.dir == dest.dir)
		{ return cur.cnt; }

		/* 현재 위치에서 동서남북 회전 */
		ROBOT next;
		for (int i = 1; i <= 4; i++) {
			next.r = cur.r;
			next.c = cur.c;
			next.dir = i;
			next.cnt = cur.cnt;
			if (visited[next.r][next.c][i]) continue;

			if (cur.dir != i) { // dir과 cnt 갱신
				if		(cur.dir + i == 3) next.cnt += 2;
				else if (cur.dir + i == 7) next.cnt += 2;
				else					   next.cnt += 1;
			}

			q.push(next);
			visited[next.r][next.c][i] = 1;
		}

		/* 현재 방향으로 k 칸 이동 가능한지 찾기 */
		for (int k = 1; k <= 3; k++) {
			next.r = cur.r + dir[cur.dir][0] * k;
			next.c = cur.c + dir[cur.dir][1] * k;
			next.dir = cur.dir;
			next.cnt = cur.cnt + 1;
			if (next.r < 1 || next.c < 1 || next.r > n || next.c > m) break;
			if (map[next.r][next.c]) break;
			if (visited[next.r][next.c][cur.dir]) continue;

			q.push(next);
			visited[next.r][next.c][cur.dir] = 1;
		}
	}
}

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf("%d", &map[i][j]);
	scanf("%d %d %d", &start.r, &start.c, &start.dir);
	scanf("%d %d %d", &dest.r, &dest.c, &dest.dir);

	start.cnt = 0;
	printf("%d\n", bfs());

	return 0;
}