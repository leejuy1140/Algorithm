#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

const int MAX = 11;

char map[MAX][MAX];
int n, m, rr, rc, br, bc;
int dr[4] = { -1, 1, 0, 0 };
int dc[4] = { 0, 0, -1, 1 };

bool visited[MAX][MAX][MAX][MAX]; // 빨간 공 위치와 파란 공 위치로 체크.
struct Info { int rr, rc, br, bc, cnt; };

int bfs()
{
	queue<Info> q;
	q.push({ rr, rc, br, bc, 0 });
	visited[rr][rc][br][bc] = true;

	while (!q.empty())
	{
		Info cur = q.front();
		q.pop();

		/* 1. 10번 이하로 빼낼 수 없음. */
		if (cur.cnt > 10) return -1;

		/* 2. 빨간공이 탈출했으면, 종료. */
		if (map[cur.rr][cur.rc] == 'O') return cur.cnt;
		
		/* 3. 파란공이 탈출했으면, 패스. */
		if (map[cur.br][cur.bc] == 'O') continue;

		for (int i = 0; i < 4; i++)
		{
			Info next = cur;
			next.cnt++;

			/* 1. 빨간공 기울이기. */
			int nrr = cur.rr;
			int nrc = cur.rc;
			while (1)
			{
				nrr += dr[i];
				nrc += dc[i];
				if (map[nrr][nrc] == '#') break; // 벽 이전에서 종료.
				next.rr = nrr;
				next.rc = nrc;
				if (map[nrr][nrc] == 'O') break; // 구멍에서 종료.
			}

			/* 2. 파란공 기울이기. */
			int nbr = cur.br;
			int nbc = cur.bc;
			while (1)
			{
				nbr += dr[i];
				nbc += dc[i];
				if (map[nbr][nbc] == '#') break; // 벽 이전에서 종료.
				next.br = nbr;
				next.bc = nbc;
				if (map[nbr][nbc] == 'O') break; // 구멍에서 종료.
			}

			/* 3. 두 공의 위치가 같음. */
			if (next.rr == next.br && next.rc == next.bc)
			{
				/* 3-1. 두 공 다 구멍이면, 패스. */
				if (map[next.rr][next.rc] == 'O') continue;
				
				/* 3-2. 두 공의 이동 거리를 계산.
				   더 적게 움직인 구슬이 먼저 벽에 부딪힌 것.
				   따라서 더 많이 움직인 구슬을 한 칸 이전으로 옮기면 됨 ! */
				int dist_r = abs(next.rr - cur.rr) + abs(next.rc - cur.rc);
				int dist_b = abs(next.br - cur.br) + abs(next.bc - cur.bc);
				if (dist_r < dist_b) // 빨간공이 먼저 벽에 닿음.
				{
					next.br -= dr[i];
					next.bc -= dc[i];
				}
				else				 // 파란공이 먼저 벽에 닿음.
				{
					next.rr -= dr[i];
					next.rc -= dc[i];
				}
			}

			/* 4. 현재 구슬의 위치 체크 후, 큐에 삽입. */
			if (visited[next.rr][next.rc][next.br][next.bc]) continue;
			visited[next.rr][next.rc][next.br][next.bc] = true;
			q.push(next);
		}
	}
	return -1;
}

int main()
{
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++)
	{
		getchar();
		for (int j = 0; j < m; j++)
		{
			scanf("%1c", &map[i][j]);
			if (map[i][j] == 'R')
			{ 
				rr = i; 
				rc = j; 
				map[i][j] = '.';
			}
			if (map[i][j] == 'B')
			{
				br = i;
				bc = j;
				map[i][j] = '.';
			}
		}
	}
	printf("%d", bfs());
	return 0;
}