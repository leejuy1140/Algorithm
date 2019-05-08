#include <iostream>
#include <queue>
#include <cmath>
using namespace std;

/*
16:00 시작
16:57 종료
57분 소요

1) 문제 이해
   1. 공은 동시에 움직임
   2. 구슬이 동시에 구멍이 빠져도 실패
   3. 동시에 같은 칸에 존재할 수 없음
2) 변수
   1. struct Ball { int rx, ry, bx, by, moveCnt; };
   2. queue<Ball> q; // BFS용 큐
   3. bool visited[MAX][MAX][MAX][MAX]; // 빨간공 파란공 위치를 함께 방문 체크
   4. char map[MAX][MAX]; // R와 B의 초기 위치는 저장 후 '.'로 변경
3) 설계
   - 가장 빠른 경우를 찾는 것이므로 BFS
   1. 빨간 공 움직이기
   2. 파란 공 움직이기
      벽을 만나면 이전으로 옮긴 후 탈출
	  구멍을 만나면 바로 탈출
   3. 같은 위치: 나중에 부딪힌 공을 한 칸 이전으로 옮긴 후 큐에 삽입
   4. 파란 공만 구멍 또는 같이 구멍: 실패이므로 패스
   5. 10회를 넘어가면 종료 후 0 출력
4) 경우의 수
   1. 빨간 공만 구멍 -> 성공
   2. 파란 공만 구멍 -> 실패
   3. 같이 구멍 -> 실패
5) 초기화
6) 가지치기
*/

const int MAX = 11;

int N, M;
char map[MAX][MAX]; // R와 B의 초기 위치는 저장 후 '.'로 변경
bool visited[MAX][MAX][MAX][MAX]; // 빨간공 파란공 위치를 함께 방문 체크
int dir[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

struct Ball { int rx, ry, bx, by, moveCnt; }; // 공들의 위치, 기울인 횟수
queue<Ball> q; // BFS용 큐

/* 입력을 처리하여 초기 공들의 위치 반환 함수. */
Ball GetInput()
{
	Ball start = { 0, 0, 0, 0, 0 };

	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> map[i][j];
			if (map[i][j] == 'R') 
			{ 
				start.rx = i;
				start.ry = j;
				map[i][j] = '.';
			}
			if (map[i][j] == 'B') 
			{ 
				start.bx = i;
				start.by = j;
				map[i][j] = '.';
			}
		}
	}
	return start;
}

/* 보드를 기울이며 10회 이내로 빨간공만 구멍에 넣으면 1 반환. */
int MoveBall(Ball ball)
{
	q.push(ball);
	visited[ball.rx][ball.ry][ball.bx][ball.by] = true;

	while (!q.empty())
	{
		Ball cur = q.front();
		q.pop();

		// 경우 1. 10회 넘어가면, 실패이므로 탈출.
		if (cur.moveCnt > 10) break;
		
		// 경우 2. 파란 공만 구멍이면, 실패이므로 다음 경우 확인.
		if (map[cur.bx][cur.by] == 'O') continue;

		// 경우 3. 빨간 공만 구멍이면, 성공이므로 1 반환.
		if (map[cur.rx][cur.ry] == 'O') return 1;

		// 1. 현재 위치에서 4 방향으로 보드 기울이기.
		for (int i = 0; i < 4; i++)
		{
			Ball next = cur;

			// 2. 빨간 공 움직이기.
			while (1)
			{
				next.rx += dir[i][0];
				next.ry += dir[i][1];
				if (map[next.rx][next.ry] == '#')		// 벽을 만나면 이전으로 옮긴 후 탈출.
				{
					next.rx -= dir[i][0];
					next.ry -= dir[i][1];
					break;
				}
				if (map[next.rx][next.ry] == 'O') break; // 구멍을 만나면 바로 탈출.
			}

			// 3. 파란 공 움직이기.
			while (1)
			{
				next.bx += dir[i][0];
				next.by += dir[i][1];
				if (map[next.bx][next.by] == '#')		// 벽을 만나면 이전으로 옮긴 후 탈출.
				{
					next.bx -= dir[i][0];
					next.by -= dir[i][1];
					break;
				}
				if (map[next.bx][next.by] == 'O') break; // 구멍을 만나면 바로 탈출.
			}

			// 4. 같은 위치면, 나중에 부딪힌 공을 한 칸 이전으로 옮긴 후 큐에 삽입.
			if (next.rx == next.bx && next.ry == next.by)
			{
				// 4-1. 둘 다 구멍이면, 실패이므로 패스.
				if (map[next.rx][next.ry] == 'O') continue;

				// 4-2. 아니라면, 누가 나중에 부딪혔는지 움직인 거리를 통해 파악
				int r_move = abs(cur.rx - next.rx) + abs(cur.ry - next.ry);
				int b_move = abs(cur.bx - next.bx) + abs(cur.by - next.by);
				if (r_move < b_move) // 파란 공이 나중에 부딪힘
				{
					next.bx -= dir[i][0];
					next.by -= dir[i][1];
				}
				else				 // 빨간 공이 나중에 부딪힘
				{
					next.rx -= dir[i][0];
					next.ry -= dir[i][1];
				}
			}

			// 5. 중복된 경우 체크 후, 큐에 삽입하여 계속해서 기울이기 진행.
			if (visited[next.rx][next.ry][next.bx][next.by]) continue;
			
			next.moveCnt++;
			q.push(next);
			visited[next.rx][next.ry][next.bx][next.by] = true;
		}
	}
	return 0;
}

int main()
{
	Ball start = GetInput();
	cout << MoveBall(start);
	return 0;
}

