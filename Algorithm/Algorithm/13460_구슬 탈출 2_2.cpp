#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

const int MAX = 11;

char map[MAX][MAX];
int n, m, rr, rc, br, bc;
int dr[4] = { -1, 1, 0, 0 };
int dc[4] = { 0, 0, -1, 1 };

bool visited[MAX][MAX][MAX][MAX]; // ���� �� ��ġ�� �Ķ� �� ��ġ�� üũ.
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

		/* 1. 10�� ���Ϸ� ���� �� ����. */
		if (cur.cnt > 10) return -1;

		/* 2. �������� Ż��������, ����. */
		if (map[cur.rr][cur.rc] == 'O') return cur.cnt;
		
		/* 3. �Ķ����� Ż��������, �н�. */
		if (map[cur.br][cur.bc] == 'O') continue;

		for (int i = 0; i < 4; i++)
		{
			Info next = cur;
			next.cnt++;

			/* 1. ������ ����̱�. */
			int nrr = cur.rr;
			int nrc = cur.rc;
			while (1)
			{
				nrr += dr[i];
				nrc += dc[i];
				if (map[nrr][nrc] == '#') break; // �� �������� ����.
				next.rr = nrr;
				next.rc = nrc;
				if (map[nrr][nrc] == 'O') break; // ���ۿ��� ����.
			}

			/* 2. �Ķ��� ����̱�. */
			int nbr = cur.br;
			int nbc = cur.bc;
			while (1)
			{
				nbr += dr[i];
				nbc += dc[i];
				if (map[nbr][nbc] == '#') break; // �� �������� ����.
				next.br = nbr;
				next.bc = nbc;
				if (map[nbr][nbc] == 'O') break; // ���ۿ��� ����.
			}

			/* 3. �� ���� ��ġ�� ����. */
			if (next.rr == next.br && next.rc == next.bc)
			{
				/* 3-1. �� �� �� �����̸�, �н�. */
				if (map[next.rr][next.rc] == 'O') continue;
				
				/* 3-2. �� ���� �̵� �Ÿ��� ���.
				   �� ���� ������ ������ ���� ���� �ε��� ��.
				   ���� �� ���� ������ ������ �� ĭ �������� �ű�� �� ! */
				int dist_r = abs(next.rr - cur.rr) + abs(next.rc - cur.rc);
				int dist_b = abs(next.br - cur.br) + abs(next.bc - cur.bc);
				if (dist_r < dist_b) // �������� ���� ���� ����.
				{
					next.br -= dr[i];
					next.bc -= dc[i];
				}
				else				 // �Ķ����� ���� ���� ����.
				{
					next.rr -= dr[i];
					next.rc -= dc[i];
				}
			}

			/* 4. ���� ������ ��ġ üũ ��, ť�� ����. */
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