#include <stdio.h>
#include <queue>
#include <algorithm>
using namespace std;

const int MAX = 101;

bool visited[MAX][MAX];
int n, m, k, map[MAX][MAX];
int dir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

int bfs(int r, int c)
{
	queue<pair<int, int>> q;
	q.push(pair<int, int>(r, c));
	visited[r][c] = 1;

	int cnt = 1;
	while (!q.empty())
	{
		pair<int, int> cur = q.front();
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			int next_r = cur.first + dir[i][0];
			int next_c = cur.second + dir[i][1];
			if (next_r < 0 || next_c < 0 || next_r >= n || next_c >= m) continue;
			if (map[next_r][next_c] || visited[next_r][next_c]) continue;

			q.push(pair<int, int>(next_r, next_c));
			visited[next_r][next_c] = 1;
			cnt++;
		}
	}
	return cnt;
}

int main()
{
	scanf("%d %d %d", &n, &m, &k);
	for (int i = 0; i < k; i++)
	{
		int x1, x2, y1, y2;
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		for (int x = x1; x < x2; x++)
			for (int y = y1; y < y2; y++)
				map[y][x] = 1;
	}
	
	vector<int> area;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (!map[i][j] && !visited[i][j])
				area.push_back(bfs(i, j));
		}
	}

	sort(area.begin(), area.end());
	printf("%d\n", area.size());
	for (int i = 0; i < area.size(); i++)
		printf("%d ", area[i]);

	return 0;
}