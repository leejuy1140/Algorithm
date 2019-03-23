#include <stdio.h>
#include <queue>
using namespace std;

const int MAX = 51;

int n, m;
char map[MAX][MAX];
struct Info { int r, c, move, key; }; // key: 6��Ʈ (MSB: f, LSB: a)
int dir[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

/* ���� ������ ��, ���谡 ��� �� ���µ�,
   �ٸ� ��ġ���� ���踦 ã��, �ٽ� �湮�� ���ɼ��� ����.
   ����, �湮 �迭�� ����� üũ !					 */
bool visited[MAX][MAX][1 << 6];

bool isDoor(char a) {
	return a >= 'A' && a <= 'Z';
}

bool isKey(char a) {
	return a >= 'a' && a <= 'z';
}

int bfs(int r, int c)
{
	queue<Info> q;
	q.push({ r, c, 0, 0 });
	visited[r][c][0] = true;

	while (!q.empty())
	{
		Info cur = q.front();
		q.pop();
		if (map[cur.r][cur.c] == '1') return cur.move;

		for (int i = 0; i < 4; i++)
		{
			int nr = cur.r + dir[i][0];
			int nc = cur.c + dir[i][1];
			if (nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
			if (map[nr][nc] == '#') continue;

			int nkey = cur.key;
			if (isKey(map[nr][nc])) // �����, ���� �߰�.
			{
				nkey |= (1 << (map[nr][nc] - 'a'));
			}
			if (isDoor(map[nr][nc])) // ���ε� ���� ������, �н�.
			{
				int door = 1 << (map[nr][nc] - 'A');
				if (!(nkey & door)) continue;
			}
			if (visited[nr][nc][nkey]) continue; // �湮 üũ.

			q.push({ nr, nc, cur.move + 1, nkey });
			visited[nr][nc][nkey] = true;
		}
	}
	return -1;
}

int main()
{
	int sr, sc; // �ν��� ���� ��ġ.
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++)
	{
		getchar();
		for (int j = 0; j < m; j++)
		{
			scanf("%1c", &map[i][j]);
			if (map[i][j] == '0')
			{ sr = i; sc = j; }
		}
	}
	int answer = bfs(sr, sc);
	printf("%d", answer);
	return 0;
}