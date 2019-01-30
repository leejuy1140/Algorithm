#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 25;

int n, map[MAX][MAX];
bool visited[MAX][MAX];
int direction[4][2] = { {0, -1}, {0, 1}, {1, 0}, {-1, 0} };

int dfs(int r, int c)
{
	visited[r][c] = 1;

	int ret = 0;
	for (int dir = 0; dir < 4; dir++)
	{
		int new_r = r + direction[dir][0];
		int new_c = c + direction[dir][1];
		
		if (new_r < 0 || new_c < 0 || new_r >= n || new_c >= n) continue;
		if (!map[new_r][new_c] || visited[new_r][new_c]) continue;
		
		ret += dfs(new_r, new_c);
	}
	return ret + 1;
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			scanf("%1d", &map[i][j]);
	}

	vector<int> result;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (map[i][j] && !visited[i][j])
				result.push_back(dfs(i, j));
		}
	}
	sort(result.begin(), result.end());
	printf("%d\n", result.size());
	for (int i = 0; i < result.size(); i++)
		printf("%d\n", result[i]);

	return 0;
}