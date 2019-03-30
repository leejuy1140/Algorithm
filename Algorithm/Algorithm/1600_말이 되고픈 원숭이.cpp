#include <iostream>
#include <queue>
using namespace std;

const int MAX = 201;
const int K_MAX = 31;

int k, n, m, map[MAX][MAX];
bool visited[MAX][MAX][K_MAX]; // 남은 K 횟수에 따라, 경로가 바뀜 -> K 횟수로 체크 !
struct Monkey { int r, c, remainK, moveCnt; };
int dr[12] = { -1, 1, 0, 0, 2, 2, -2, -2, -1, 1, -1, 1 };
int dc[12] = { 0, 0, -1, 1, -1, 1, -1, 1, 2, 2, -2, -2 };

int bfs()
{
	queue<Monkey> q;
	q.push({ 0, 0, k, 0 });
	for (int i = 0; i < K_MAX; i++) visited[0][0][i] = true;

	while (!q.empty())
	{
		Monkey cur = q.front();
		q.pop();
		if (cur.r == n - 1 && cur.c == m - 1) return cur.moveCnt;

		for (int i = 0; i < 12; i++)
		{
			if (!cur.remainK && i == 4) break; // k를 다 썼다면, 인접 칸만 이동.

			int nr = cur.r + dr[i];
			int nc = cur.c + dc[i];
			if (nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
			if (map[nr][nc]) continue;

			int remain = cur.remainK;
			if (i >= 4) remain--;
			if (visited[nr][nc][remain]) continue;
			
			q.push({ nr, nc, remain, cur.moveCnt + 1 });
			visited[nr][nc][remain] = true;
		}
	}
	return -1;
}

int main()
{
	scanf("%d", &k);
	scanf("%d %d", &m, &n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			scanf("%d", &map[i][j]);

	int answer = bfs();
	printf("%d", answer);
	return 0;
}