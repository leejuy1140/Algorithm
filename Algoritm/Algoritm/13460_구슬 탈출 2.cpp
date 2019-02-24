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

		/* 1. ���ÿ� �������ų�, �Ķ� ���� ��������, �ٸ� ��� ���Ѻ���.
		   2. ���� ���� ��������, cnt ��ȯ.
		   3. 10ȸ �ȿ� �������� �ȶ�������, -1 ��ȯ.					 */
		if (cur.cnt > 10) return -1;
		if (board[cur.rr][cur.rc] == 'O' && board[cur.br][cur.bc] == 'O') continue;
		if (board[cur.rr][cur.rc] == 'O') return cur.cnt;
		if (board[cur.br][cur.bc] == 'O') continue;

		/* 4 ���� ����̱� */
		for (int i = 0; i < 4; i++)
		{
			/* ���� ��ġ���� i �������� ����̱�. (���� ������ �Ķ� ������ ���ÿ� ������.) */
			Status next = cur;

			/* ���̻� �������� ���� �� ���� ����̱�. */
			bool red = 0, blue = 0;
			while (!red || !blue)
			{
				if (!red)  { next.rr += dir[i][0]; next.rc += dir[i][1]; }
				if (!blue) { next.br += dir[i][0]; next.bc += dir[i][1]; }
				
				/* 1. ���� �ε��� ���� ���̻� �������� �ʰ�, �÷��� ó��.
				   2. ���ۿ� ���� �ʾҴµ�, �� ������ ���� ĭ�� �ִ� ���. */
				if (board[next.rr][next.rc] == '#' || (blue && next.rr == next.br && next.rc == next.bc))
				{
					next.rr += (-1 * dir[i][0]); // ���� �ε����� �ٷ� ������ �̵�.
					next.rc += (-1 * dir[i][1]);
					red = 1;
				}
				if (board[next.br][next.bc] == '#' || (red && next.rr == next.br && next.rc == next.bc))
				{
					next.br += (-1 * dir[i][0]);
					next.bc += (-1 * dir[i][1]);
					blue = 1;
				}

				/* 3. ���ۿ� �� ���, �� �̻� �������� �ʰ� �÷��� ó�� */
				if (!red && board[next.rr][next.rc] == 'O')  { red = 1; continue; }
				if (!blue && board[next.br][next.bc] == 'O') { blue = 1; continue; }
			}
			/* ������ ������ �� ��, ���� ���� �Ķ� ���� ���°� ������ ������, �н�. */
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