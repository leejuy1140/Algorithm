#include <stdio.h>
#include <queue>
using namespace std;

#define SIZE 105

bool visited[SIZE][SIZE][4]; // �ش� ��ġ�� K��ŭ �������� ������ ���
int n, m, map[SIZE][SIZE];
int dir[5][2] = { {0, 0}, {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

struct ROBOT { int r, c, dir, cnt; };
ROBOT start, dest;

int bfs()
{
	queue<ROBOT> q;
	q.push(start);

	while (!q.empty())
	{
		ROBOT cur = q.front();
		q.pop();

		if (cur.r == dest.r && cur.c == dest.c)
		{
			if (cur.dir == dest.dir) return cur.cnt;
			if (cur.dir + dest.dir == 3 || cur.dir + dest.dir == 7) return cur.cnt += 2;
			else return cur.cnt += 1;
		}

		for (int i = 1; i <= 4; i++)
		{
			for (int k = 1; k <= 3; k++)
			{
				/* �ش� �������� kĭ �̵� �������� ã�� */
				ROBOT next;
				next.r = cur.r + (dir[i][0] * k);
				next.c = cur.c + (dir[i][1] * k);
				if (next.r < 1 || next.c < 1 || next.r > n || next.c > m) break;
				if (map[next.r][next.c] || visited[next.r][next.c][k]) break;

				/* �� �� ������ �� �������� ȸ�� ��, dir�� cnt ���� */
				next.dir = i;
				next.cnt = cur.cnt + 1;
				if (cur.dir != next.dir) // ���� ����� ���� ���� ���, dir�� cnt ����.
				{
					if (cur.dir + i == 3 || cur.dir + i == 7) next.cnt += 2;
					else next.cnt += 1;
				}

				q.push(next);
				visited[next.r][next.c][k] = 1;
			}
		}
	}
}

int main()
{
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf("%d", &map[i][j]);
	scanf("%d %d %d", &start.r, &start.c, &start.dir);
	scanf("%d %d %d", &dest.r, &dest.c, &dest.dir);

	start.cnt = dest.cnt = 0;
	printf("%d\n", bfs());

	return 0;
}