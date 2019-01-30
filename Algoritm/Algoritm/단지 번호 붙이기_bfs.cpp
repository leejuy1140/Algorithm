#include <stdio.h>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 25;

int n;
bool map[MAX][MAX], visited[MAX][MAX];
int dir[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

int bfs(int r, int c)
{
	queue<pair<int, int>> q;
	q.push(pair<int, int>(r, c));
	visited[r][c] = 1;

	int cnt = 0;
	while (!q.empty())
	{
		pair<int, int> cur = q.front();
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			int new_r = cur.first + dir[i][0];
			int new_c = cur.second + dir[i][1];

			if (new_r < 0 || new_c < 0 || new_r >= n || new_c >= n) continue;
			if (!map[new_r][new_c] || visited[new_r][new_c]) continue;

			q.push(pair<int, int>(new_r, new_c));
			visited[new_r][new_c] = 1;
			cnt++;
		}
	}
	return cnt;
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			scanf("%1d", &map[i][j]);

	vector<int> result;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (map[i][j] && !visited[i][j])
				result.push_back(bfs(i, j));
		}
	}
	printf("%d\n", result.size());
	sort(result.begin(), result.end());
	for (int i = 0; i < result.size(); i++)
		printf("%d\n", result[i]);

	return 0;
}