#include <stdio.h>
#include <queue>
using namespace std;

const int MAX = 101;

bool visited[MAX][MAX];
int n, m, map[MAX][MAX];
int dir[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
typedef pair<int, pair<int, int>> info_t;

int bfs()
{
	priority_queue<info_t, vector<info_t>, greater<info_t>> pq;
	pq.push(make_pair(0, make_pair(0, 0))); // 벽 부순 개수.
	visited[0][0] = 1;

	while (!pq.empty())
	{
		info_t cur = pq.top();
		pq.pop();

		if (cur.second.first == n - 1 && cur.second.second == m - 1)
			return cur.first;

		for (int i = 0; i < 4; i++)
		{
			int nr = cur.second.first + dir[i][0];
			int nc = cur.second.second + dir[i][1];
			if (nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
			if (visited[nr][nc]) continue;

			if(map[nr][nc]) pq.push(make_pair(cur.first + 1, make_pair(nr, nc)));
			else			pq.push(make_pair(cur.first, make_pair(nr, nc)));
			visited[nr][nc] = 1;
		}
	}
}

int main()
{
	scanf("%d %d", &m, &n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			scanf("%1d", &map[i][j]);
	printf("%d", bfs());
	return 0;
}