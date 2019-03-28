#include <iostream>
#include <queue>
using namespace std;

const int MAX = 51;

int n;
char map[MAX][MAX];
bool visited[MAX][MAX][2]; // [�߾� ��ǥ][���] �湮 üũ.
int dr[4] = { 0, 0, -1, 1 };
int dc[4] = { -1, 1, 0, 0 };
struct Log { int r, c, cnt, shape; };
// �߾���ǥ, ���� Ƚ��, ��� (1: ����, 0: ����), ȸ�� ���� ����.

/* �ش� ��ǥ�� ���� �ȿ� �ְ� ������ ������, �� ��ȯ. */
bool CheckRange(int r, int c)
{
	if (r < 0 || c < 0 || r >= n || c >= n) return false;
	if (map[r][c] == '1') return false;
	return true;
}

/* �ش� �볪���� ȸ���� �� ������, ���� ��ȯ. */
bool CanTurn(Log log)
{
	for (int i = log.r - 1; i <= log.r + 1; i++)
		for (int j = log.c - 1; j <= log.c + 1; j++)
			if (!CheckRange(i, j)) return false;
	return true;
}

int bfs(Log _start)
{
	queue<Log> q;
	q.push(_start);
	visited[_start.r][_start.c][_start.shape] = 0;

	while (!q.empty())
	{
		Log cur = q.front();
		q.pop();

		if (map[cur.r][cur.c] == 'E') // ���� ��ġ���� Ȯ��.
		{
			if (cur.shape) // ���� Ȯ��.
			{
				if (map[cur.r][cur.c - 1] == 'E')
					if (map[cur.r][cur.c + 1] == 'E') return cur.cnt;
			}
			else
			{
				if (map[cur.r - 1][cur.c] == 'E')
					if (map[cur.r + 1][cur.c] == 'E') return cur.cnt;
			}
		}

		// 1. 4 �������� �̵�.
		for (int i = 0; i < 4; i++)
		{
			int nr = cur.r + dr[i];
			int nc = cur.c + dc[i];

			// 2. �볪���� ������ ����ų�, ������ �ִ��� üũ.
			if (!CheckRange(nr, nc)) continue;
			if (cur.shape)
			{
				if (!CheckRange(nr, nc + 1)) continue;
				if (!CheckRange(nr, nc - 1)) continue;
			}
			else
			{
				if (!CheckRange(nr + 1, nc)) continue;
				if (!CheckRange(nr - 1, nc)) continue;
			}
			
			// 3. �湮 üũ.
			if(visited[nr][nc][cur.shape] != -1)
				if (visited[nr][nc][cur.shape]) continue;

			// 4. ȸ�� ��������, ��� �״�� ť�� ����.
			q.push({ nr, nc, cur.cnt + 1, cur.shape });
			visited[nr][nc][cur.shape] = true;
		}

		// 5. ȸ�� �����ϴٸ�, ȸ���� ��, ť�� ����.
		if (CanTurn(cur))
		{
			int next_shape = (cur.shape + 1) % 2;
			if (visited[cur.r][cur.c][next_shape] != -1)
				if (visited[cur.r][cur.c][next_shape]) continue;
			
			q.push({ cur.r, cur.c, cur.cnt + 1, next_shape });
			visited[cur.r][cur.c][next_shape] = true;
		}
	}
	return 0;
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		getchar();
		for (int j = 0; j < n; j++)
		{
			scanf("%1c", &map[i][j]);
			visited[i][j][0] = false;
			visited[i][j][1] = false;
		}
	}

	// 1. ������ ó�� �߾� ��ǥ�� ��� ã��.
	Log start;
	bool flag = false;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (map[i][j] == 'B')
			{
				if (map[i + 1][j] == 'B') start = { i + 1, j, 0, 0 };
				else					  start = { i, j + 1, 0, 1 };
				
				flag = true;
				break;
			}
		}
		if (flag) break;
	}

	// 2. ���� �ű��.
	int answer = bfs(start);
	printf("%d", answer);

	return 0;
}