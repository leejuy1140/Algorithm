#include <stdio.h>
#include <queue>
using namespace std;

const int MAX = 1001;

int n, m, map[MAX][MAX], visited[MAX][MAX]; // ��, ��
int dir[4][2] = { {-1, 0}, {0, 1}, {0, -1}, {1, 0} }; // �ϵ�����
struct INFO
{
	int r, c, cnt, ax;

	void setInfo(int _r, int _c, int _cnt, int _ax)
	{ r = _r; c = _c; cnt = _cnt; ax = _ax; }
};

int bfs(INFO first)
{
	queue<INFO> q;
	q.push(first);
	visited[first.r][first.c] = 1;

	while (!q.empty())
	{
		INFO cur = q.front();
		q.pop();

		if (cur.r == n - 1 && cur.c == m - 1) return cur.cnt;

		for (int i = 0; i < 4; i++)
		{
			INFO next;
			next.setInfo(cur.r + dir[i][0], cur.c + dir[i][1], cur.cnt + 1, cur.ax);
			
			if (next.r < 0 || next.c < 0 || next.r >= n || next.c >= m) continue;
			if (visited[next.r][next.c] == 1) continue;

			// ���� �μ��� ������ ���� �̹� ���� �μ� �ֵ��� �������� ���ϵ���
			// �ߺ� push �Ǵ� �� ���� !!!
			if (visited[next.r][next.c] == 2 && !next.ax) continue;

			if (map[next.r][next.c] && next.ax)
			{
				next.ax = 0;
				q.push(next);

				// ���⼭ �μ� ���� ������ ���� �ƴԿ��� �ұ��ϰ�, �����븦 ǥ���س�,
				// �ٸ� ������ ���� �������� ���� �� �����Ƿ�, 2�� �ٸ��� ǥ�� !
				visited[next.r][next.c] = 2;
			}
			if (!map[next.r][next.c])
			{
				q.push(next);

				// ���� �μ��� ������ ���� 2�� ǥ����,
				// ���� ���� �μ��� ���� �ְ� ������ �� �ֵ��� !!!
				if (!next.ax) visited[next.r][next.c] = 2;
				else	  	  visited[next.r][next.c] = 1;
			}
		}
	}
	return -1;
}

int main()
{
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			scanf("%1d", &map[i][j]);

	INFO start;
	start.setInfo(0, 0, 1, 1);
	printf("%d", bfs(start));

	return 0;
}