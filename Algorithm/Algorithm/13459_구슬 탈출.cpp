#include <iostream>
#include <queue>
#include <cmath>
using namespace std;

/*
16:00 ����
16:57 ����
57�� �ҿ�

1) ���� ����
   1. ���� ���ÿ� ������
   2. ������ ���ÿ� ������ ������ ����
   3. ���ÿ� ���� ĭ�� ������ �� ����
2) ����
   1. struct Ball { int rx, ry, bx, by, moveCnt; };
   2. queue<Ball> q; // BFS�� ť
   3. bool visited[MAX][MAX][MAX][MAX]; // ������ �Ķ��� ��ġ�� �Բ� �湮 üũ
   4. char map[MAX][MAX]; // R�� B�� �ʱ� ��ġ�� ���� �� '.'�� ����
3) ����
   - ���� ���� ��츦 ã�� ���̹Ƿ� BFS
   1. ���� �� �����̱�
   2. �Ķ� �� �����̱�
      ���� ������ �������� �ű� �� Ż��
	  ������ ������ �ٷ� Ż��
   3. ���� ��ġ: ���߿� �ε��� ���� �� ĭ �������� �ű� �� ť�� ����
   4. �Ķ� ���� ���� �Ǵ� ���� ����: �����̹Ƿ� �н�
   5. 10ȸ�� �Ѿ�� ���� �� 0 ���
4) ����� ��
   1. ���� ���� ���� -> ����
   2. �Ķ� ���� ���� -> ����
   3. ���� ���� -> ����
5) �ʱ�ȭ
6) ����ġ��
*/

const int MAX = 11;

int N, M;
char map[MAX][MAX]; // R�� B�� �ʱ� ��ġ�� ���� �� '.'�� ����
bool visited[MAX][MAX][MAX][MAX]; // ������ �Ķ��� ��ġ�� �Բ� �湮 üũ
int dir[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

struct Ball { int rx, ry, bx, by, moveCnt; }; // ������ ��ġ, ����� Ƚ��
queue<Ball> q; // BFS�� ť

/* �Է��� ó���Ͽ� �ʱ� ������ ��ġ ��ȯ �Լ�. */
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

/* ���带 ����̸� 10ȸ �̳��� �������� ���ۿ� ������ 1 ��ȯ. */
int MoveBall(Ball ball)
{
	q.push(ball);
	visited[ball.rx][ball.ry][ball.bx][ball.by] = true;

	while (!q.empty())
	{
		Ball cur = q.front();
		q.pop();

		// ��� 1. 10ȸ �Ѿ��, �����̹Ƿ� Ż��.
		if (cur.moveCnt > 10) break;
		
		// ��� 2. �Ķ� ���� �����̸�, �����̹Ƿ� ���� ��� Ȯ��.
		if (map[cur.bx][cur.by] == 'O') continue;

		// ��� 3. ���� ���� �����̸�, �����̹Ƿ� 1 ��ȯ.
		if (map[cur.rx][cur.ry] == 'O') return 1;

		// 1. ���� ��ġ���� 4 �������� ���� ����̱�.
		for (int i = 0; i < 4; i++)
		{
			Ball next = cur;

			// 2. ���� �� �����̱�.
			while (1)
			{
				next.rx += dir[i][0];
				next.ry += dir[i][1];
				if (map[next.rx][next.ry] == '#')		// ���� ������ �������� �ű� �� Ż��.
				{
					next.rx -= dir[i][0];
					next.ry -= dir[i][1];
					break;
				}
				if (map[next.rx][next.ry] == 'O') break; // ������ ������ �ٷ� Ż��.
			}

			// 3. �Ķ� �� �����̱�.
			while (1)
			{
				next.bx += dir[i][0];
				next.by += dir[i][1];
				if (map[next.bx][next.by] == '#')		// ���� ������ �������� �ű� �� Ż��.
				{
					next.bx -= dir[i][0];
					next.by -= dir[i][1];
					break;
				}
				if (map[next.bx][next.by] == 'O') break; // ������ ������ �ٷ� Ż��.
			}

			// 4. ���� ��ġ��, ���߿� �ε��� ���� �� ĭ �������� �ű� �� ť�� ����.
			if (next.rx == next.bx && next.ry == next.by)
			{
				// 4-1. �� �� �����̸�, �����̹Ƿ� �н�.
				if (map[next.rx][next.ry] == 'O') continue;

				// 4-2. �ƴ϶��, ���� ���߿� �ε������� ������ �Ÿ��� ���� �ľ�
				int r_move = abs(cur.rx - next.rx) + abs(cur.ry - next.ry);
				int b_move = abs(cur.bx - next.bx) + abs(cur.by - next.by);
				if (r_move < b_move) // �Ķ� ���� ���߿� �ε���
				{
					next.bx -= dir[i][0];
					next.by -= dir[i][1];
				}
				else				 // ���� ���� ���߿� �ε���
				{
					next.rx -= dir[i][0];
					next.ry -= dir[i][1];
				}
			}

			// 5. �ߺ��� ��� üũ ��, ť�� �����Ͽ� ����ؼ� ����̱� ����.
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

