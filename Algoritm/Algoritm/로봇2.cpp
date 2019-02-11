#include <stdio.h>
#include <queue>
using namespace std;

#define SIZE 105

/* 어떤 방향으로 좌표에 도달하느냐에 따라,
   명령 횟수가 달라지기 때문에, 방향으로 방문 체크
   
   최소로 들어로는 경우가 무시될 수 있기 때문에, 명령 횟수로 체크 !
   (명령 횟수가 이전 횟수 보다 작으면, 큐에 삽입해 최소값 탐색 진행) */
int visited[SIZE][SIZE][5];

int n, m, map[SIZE][SIZE];
int dir[5][2] = { {0, 0}, {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

struct ROBOT { int r, c, dir, cnt; };
ROBOT start, dest;

int bfs()
{
	queue<ROBOT> q;
	q.push(start);

	int answer = 9999999;

	while (!q.empty()) {
		ROBOT cur = q.front();
		q.pop();

		if (cur.r == dest.r && cur.c == dest.c && cur.dir == dest.dir)
		{
			answer = answer < cur.cnt ? answer : cur.cnt;
			continue;
		}

		for (int i = 1; i <= 4; i++) {
			for (int k = 0; k <= 3; k++) {
				/* i 방향으로 k 칸 이동 가능한지 찾기 */
				ROBOT next;
				next.r = cur.r + (dir[i][0] * k);
				next.c = cur.c + (dir[i][1] * k);
				next.dir = i;
				next.cnt = cur.cnt + 1;		// 이동 명령 카운팅
				if (!k) next.cnt = cur.cnt; // k가 0이면 이동 안하고, 제자리 회전만 고려

				/* 회전이 필요한 경우, cnt 갱신 */
				if (cur.dir != i) {
					if (cur.dir + i == 3) next.cnt += 2;
					else if (cur.dir + i == 7) next.cnt += 2;
					else                       next.cnt += 1;
				}

				if (next.r < 1 || next.c < 1 || next.r > n || next.c > m) break;
				if (map[next.r][next.c]) break;

				/* 방문한 적이 있는데, 현재값이 0이거나, 이전보다 최소가 아니라면, 패스 ! */
				if (visited[next.r][next.c][i])
					if (!next.cnt || visited[next.r][next.c][i] <= next.cnt) continue;

				q.push(next);
				visited[next.r][next.c][i] = next.cnt;
			}
		}
	}
	return answer;
}

int main()
{
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