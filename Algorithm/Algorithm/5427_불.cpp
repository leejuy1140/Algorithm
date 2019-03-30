#include <stdio.h>
#include <string.h>
#include <queue>
using namespace std;

const int MAX = 1001;

char map[MAX][MAX];
bool visited[MAX][MAX]; // 상근이의 방문 체크.
int n, m, fire[MAX][MAX]; // 불이 번지는 시간 저장.
int dr[4] = { 0, 0, -1, 1 };
int dc[4] = { -1, 1, 0, 0 };

void SpreadFire()
{
	queue<pair<int, pair<int, int>>> q; // 시간, 좌표
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (map[i][j] != '*') continue;
			q.push(make_pair(0, make_pair(i, j)));
			fire[i][j] = 0;
		}
	}

	while (!q.empty())
	{
		int rr = q.front().second.first;
		int cc = q.front().second.second;
		int time = q.front().first;
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			int nr = rr + dr[i];
			int nc = cc + dc[i];
			if (nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
			if (fire[nr][nc] != -1 && fire[nr][nc] <= time + 1) continue;
			if (map[nr][nc] == '#') continue;

			q.push(make_pair(time + 1, make_pair(nr, nc)));
			fire[nr][nc] = time + 1;
		}
	}
}

int Escape(int r, int c)
{
	queue<pair<int, pair<int, int>>> q; // 시간, 좌표
	q.push(make_pair(0, make_pair(r, c)));
	visited[r][c] = true;

	while (!q.empty())
	{
		int rr = q.front().second.first;
		int cc = q.front().second.second;
		int time = q.front().first;
		q.pop();
		if (!rr || !cc || rr == n - 1 || cc == m - 1) return time + 1;

		for (int i = 0; i < 4; i++)
		{
			int nr = rr + dr[i];
			int nc = cc + dc[i];
			if (nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
			if (fire[nr][nc] != -1 && fire[nr][nc] <= time + 1) continue;
			if (map[nr][nc] == '#' || visited[nr][nc]) continue;

			q.push(make_pair(time + 1, make_pair(nr, nc)));
			visited[nr][nc] = true;
		}
	}
	return -1;
}

int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
	{
		int sr, sc;
		scanf("%d %d", &m, &n);
		for (int i = 0; i < n; i++)
		{
			getchar();
			for (int j = 0; j < m; j++)
			{
				fire[i][j] = -1;
				visited[i][j] = false;
				scanf("%1c", &map[i][j]);
				if (map[i][j] == '@') { sr = i; sc = j; }
			}
		}

		// 불이 시간 순으로 퍼짐.
		SpreadFire();

		// 상근 탈출.printf("IMPOSSIBLE\n");
		int answer = Escape(sr, sc);
		if (answer == -1) printf("IMPOSSIBLE\n");
		else			  printf("%d\n", answer);
	}
	return 0;
}