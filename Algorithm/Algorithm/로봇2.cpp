#include <stdio.h>
#include <queue>
using namespace std;

#define SIZE 105

/* � �������� ��ǥ�� �����ϴ��Ŀ� ����,
   ��� Ƚ���� �޶����� ������, �������� �湮 üũ
   
   �ּҷ� ���δ� ��찡 ���õ� �� �ֱ� ������, ��� Ƚ���� üũ !
   (��� Ƚ���� ���� Ƚ�� ���� ������, ť�� ������ �ּҰ� Ž�� ����) */
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
				/* i �������� k ĭ �̵� �������� ã�� */
				ROBOT next;
				next.r = cur.r + (dir[i][0] * k);
				next.c = cur.c + (dir[i][1] * k);
				next.dir = i;
				next.cnt = cur.cnt + 1;		// �̵� ��� ī����
				if (!k) next.cnt = cur.cnt; // k�� 0�̸� �̵� ���ϰ�, ���ڸ� ȸ���� ���

				/* ȸ���� �ʿ��� ���, cnt ���� */
				if (cur.dir != i) {
					if (cur.dir + i == 3) next.cnt += 2;
					else if (cur.dir + i == 7) next.cnt += 2;
					else                       next.cnt += 1;
				}

				if (next.r < 1 || next.c < 1 || next.r > n || next.c > m) break;
				if (map[next.r][next.c]) break;

				/* �湮�� ���� �ִµ�, ���簪�� 0�̰ų�, �������� �ּҰ� �ƴ϶��, �н� ! */
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