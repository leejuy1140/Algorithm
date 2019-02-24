#include <stdio.h>
#include <queue>
using namespace std;

const int MAX = 15;

int n, m;
char board[MAX][MAX];
bool visited[MAX][MAX][MAX][MAX];
int dir[4][2] = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} };

class Status
{
public: 
	int rr, rc, br, bc, cnt;  
	Status(int rr, int rc, int br, int bc, int cnt)
	{
		this->rr = rr; this->rc = rc;
		this->br = br; this->bc = bc; this->cnt = cnt;
	}
};

int bfs(Status start)
{
	queue<Status> q;
	q.push(start);
	visited[start.rr][start.rc][start.br][start.bc] = 1;

	while (!q.empty())
	{
		Status cur = q.front();
		q.pop();

		/* 1. 동시에 떨어지거나, 파란 공만 떨어지면, 다른 경우 지켜보기.
		   2. 빨간 공만 떨어지면, cnt 반환.
		   3. 10회 안에 빨간공이 안떨어지면, -1 반환.					 */
		if (cur.cnt > 10) return -1;
		if (board[cur.rr][cur.rc] == 'O' && board[cur.br][cur.bc] == 'O') continue;
		if (board[cur.rr][cur.rc] == 'O') return cur.cnt;
		if (board[cur.br][cur.bc] == 'O') continue;

		/* 4 방향 기울이기 */
		for (int i = 0; i < 4; i++)
		{
			/* 현재 위치에서 i 방향으로 기울이기. (빨간 구슬과 파란 구슬은 동시에 움직임.) */
			Status next = cur;

			/* 더이상 움직이지 않을 때 까지 기울이기. */
			bool red = 0, blue = 0;
			while (!red || !blue)
			{
				if (!red)  { next.rr += dir[i][0]; next.rc += dir[i][1]; }
				if (!blue) { next.br += dir[i][0]; next.bc += dir[i][1]; }
				
				/* 1. 벽에 부딪힌 공은 더이상 움직이지 않게, 플래그 처리.
				   2. 구멍에 들어가지 않았는데, 두 구슬이 같은 칸에 있는 경우. */
				if (board[next.rr][next.rc] == '#' || (blue && next.rr == next.br && next.rc == next.bc))
				{
					next.rr += (-1 * dir[i][0]); // 벽에 부딪히기 바로 전으로 이동.
					next.rc += (-1 * dir[i][1]);
					red = 1;
				}
				if (board[next.br][next.bc] == '#' || (red && next.rr == next.br && next.rc == next.bc))
				{
					next.br += (-1 * dir[i][0]);
					next.bc += (-1 * dir[i][1]);
					blue = 1;
				}

				/* 3. 구멍에 들어간 경우, 더 이상 움직이지 않게 플래그 처리 */
				if (!red && board[next.rr][next.rc] == 'O')  { red = 1; continue; }
				if (!blue && board[next.br][next.bc] == 'O') { blue = 1; continue; }
			}
			/* 구슬은 굴리고 난 후, 빨간 공과 파란 공의 상태가 이전과 같으면, 패스. */
			if (visited[next.rr][next.rc][next.br][next.bc]) continue;

			next.cnt++;
			q.push(next);
			visited[next.rr][next.rc][next.br][next.bc] = 1;
		}
	}
	return -1;
}

int main()
{
	int srr, src, sbr, sbc;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++)
	{
		getchar();
		for (int j = 0; j < m; j++)
		{
			scanf("%1c", &board[i][j]);
			if (board[i][j] == 'R') { srr = i; src = j; }
			if (board[i][j] == 'B') { sbr = i; sbc = j; }
		}
	}
	Status start(srr, src, sbr, sbc, 0);
	printf("%d\n", bfs(start));
	return 0;
}