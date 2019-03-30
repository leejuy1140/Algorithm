#include <stdio.h>
#include <string.h>
#include <queue>
using namespace std;

const int MAX = 101;

int n;
char map[MAX][MAX];
bool visited[MAX][MAX];
int dir[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

bool isSameColor(int curColor, int adjColor)
{
	if (curColor == 'G' && adjColor == 'R')  return true;
	if (curColor == 'R' && adjColor == 'G')  return true;
	return false;
}

/* who 0 -> 적록색약 X, 1-> 적록색약 O */
int bfs(int r, int c, int who)
{
	queue<pair<int, int>> q;
	q.push(make_pair(r, c));
	visited[r][c] = 1;

	while (!q.empty()) {
		pair<int, int> cur = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nr = cur.first + dir[i][0];
			int nc = cur.second + dir[i][1];
			if (nr < 0 || nc < 0 || nr >= n || nc >= n) continue;
			if (visited[nr][nc]) continue;
			
			int curColor = map[cur.first][cur.second];
			int adjColor = map[nr][nc];
			
			if (curColor != map[nr][nc]) { // 색맹에게 R과 G는 같은 색
				if (who && !isSameColor(curColor, adjColor)) continue;
				if (!who) continue;
			}
			q.push(make_pair(nr, nc));
			visited[nr][nc] = 1;
		}
	}
	return 1;
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		getchar();
		for (int j = 0; j < n; j++)
			scanf("%1c", &map[i][j]);
	}

	int ans1 = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (!visited[i][j])
				ans1 += bfs(i, j, 0);
		}
	}

	for (int i = 0; i < n; i++)
		memset(&visited[i], 0, n);
	
	int ans2 = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (!visited[i][j])
				ans2 += bfs(i, j, 1);
		}
	}

	printf("%d %d\n", ans1, ans2);
	return 0;
}