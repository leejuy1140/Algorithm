#include <stdio.h>
#include <queue>
using namespace std;

const int MAX = 51;

int n, m;
char map[MAX][MAX];
struct Info { int r, c, move, key; }; // key: 6비트 (MSB: f, LSB: a)
int dir[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

/* 문을 만났을 때, 열쇠가 없어서 못 갔는데,
   다른 위치에서 열쇠를 찾고, 다시 방문할 가능성이 있음.
   따라서, 방문 배열은 열쇠로 체크 !					 */
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
			if (isKey(map[nr][nc])) // 열쇠면, 열쇠 추가.
			{
				nkey |= (1 << (map[nr][nc] - 'a'));
			}
			if (isDoor(map[nr][nc])) // 문인데 열쇠 없으면, 패스.
			{
				int door = 1 << (map[nr][nc] - 'A');
				if (!(nkey & door)) continue;
			}
			if (visited[nr][nc][nkey]) continue; // 방문 체크.

			q.push({ nr, nc, cur.move + 1, nkey });
			visited[nr][nc][nkey] = true;
		}
	}
	return -1;
}

int main()
{
	int sr, sc; // 민식이 시작 위치.
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