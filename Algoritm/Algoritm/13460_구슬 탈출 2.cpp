#include <stdio.h>
#include <queue>
using namespace std;

const int MAX = 15;

int n, m;
char board[MAX][MAX];
bool redVisited[MAX][MAX];
bool blueVisited[MAX][MAX];
int dir[4][2] = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} };

class Status
{
public: 
	int rr, rc, br, bc, cnt;  
	Status(int rr, int rc, int br, int bc, int cnt)
	{
		this->rr = rr; this->rc = rc;
		this->br = br; this->bc = bc;
		this->cnt = cnt;
	}
};

void showStatus(Status cur)
{
	printf("\n[%d]\n", cur.cnt);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (i == cur.rr && j == cur.rc)
			{
				printf("R");
				continue;
			}
			if (i == cur.br && j == cur.bc)
			{
				printf("B");
				continue;
			}
			if (board[i][j] == 'R' || board[i][j] == 'B') printf(".");
			else										  printf("%c", board[i][j]);
		}
		printf("\n");
	}
}

int bfs(Status start)
{
	queue<Status> q;
	q.push(start);
	redVisited[start.rr][start.rc] = 1;
	blueVisited[start.br][start.bc] = 1;

	int blueCnt = 0;
	while (!q.empty())
	{
		Status cur = q.front();
		q.pop();
		//showStatus(cur);

		if (cur.cnt > 10) return -1; // 10ȸ �ȿ� �ȶ�������, -1.
		if (board[cur.rr][cur.rc] == 'O' && board[cur.br][cur.bc] == 'O') return -1; // ���ÿ� ��������, -1.
		if (board[cur.rr][cur.rc] == 'O') return cur.cnt;
		if (board[cur.br][cur.bc] == 'O') continue;

		/* 4 ���� ����̱� */
		for (int i = 0; i < 4; i++)
		{
			/* ���� ��ġ���� i �������� ����̱�.
			   (���� ������ �Ķ� ���� ������ ������ !) */
			Status next = cur;

			/* ���̻� �������� ���� �� ���� ����̱�. */
			bool red = 0, blue = 0;
			while (!red || !blue)
			{
				if (!red)
				{
					next.rr += dir[i][0];
					next.rc += dir[i][1];
				}
				if (!blue)
				{
					next.br += dir[i][0];
					next.bc += dir[i][1];
				}

				/* ���� �ε��� ���. */
				if (board[next.rr][next.rc] == '#' || next.rr < 0 || next.rr >= n || next.rc < 0 || next.rc >= m)
				{
					next.rr += (-1 * dir[i][0]);
					next.rc += (-1 * dir[i][1]);
					red = 1;
				}
				if (board[next.br][next.bc] == '#' || next.br < 0 || next.br >= n || next.bc < 0 || next.bc >= m)
				{
					next.br += (-1 * dir[i][0]);
					next.bc += (-1 * dir[i][1]);
					blue = 1;
				}

				/* ���ۿ� �� ��� */
				if (!red && board[next.rr][next.rc] == 'O')
				{
					red = 1;
					continue;
				}
				if (!blue && board[next.br][next.bc] == 'O')
				{
					blue = 1;
					continue;
				}

				/* ���ۿ� ���� �ʾҴµ�, �� ������ ���� ĭ�� �ִ� ���. */
				if (red && next.rr == next.br && next.rc == next.bc)
				{
					next.br += (-1 * dir[i][0]);
					next.bc += (-1 * dir[i][1]);
					blue = 1;
				}
				if (blue && next.rr == next.br && next.rc == next.bc)
				{
					next.rr += (-1 * dir[i][0]);
					next.rc += (-1 * dir[i][1]);
					red = 1;
				}
			}
			//if (redVisited[next.rr][next.rc] && blueVisited[next.br][next.bc]) continue;

			next.cnt++;
			q.push(next);
			redVisited[next.rr][next.rc] = 1;
			blueVisited[next.br][next.bc] = 1;
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

	int res = bfs(start);
	printf("%d\n", res);

	return 0;
}