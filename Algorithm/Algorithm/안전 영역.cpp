#include <stdio.h>
#include <string.h>
#include <queue>
using namespace std;

const int MAX = 101;

int n, map[MAX][MAX];
bool visited[MAX][MAX], flood[MAX][MAX]; // 1 이면 침수
int dir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

void raining(int height)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (map[i][j] <= height) flood[i][j] = 1;
}

int bfs(int r, int c)
{
	queue<pair<int, int>> q;
	q.push(pair<int, int>(r, c));
	visited[r][c] = 1;

	while (!q.empty())
	{
		pair<int, int> cur = q.front();
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			int next_r = cur.first + dir[i][0];
			int next_c = cur.second + dir[i][1];
			if (next_r < 0 || next_c < 0 || next_r >= n || next_c >= n) continue;
			if (flood[next_r][next_c] || visited[next_r][next_c]) continue;

			q.push(pair<int, int>(next_r, next_c));
			visited[next_r][next_c] = 1;
		}
	}
	return 1;
}

int main()
{
	scanf("%d", &n);
	int maxHeight = 0;
	int minHeight = MAX;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			scanf("%d", &map[i][j]);
			if (map[i][j] > maxHeight) maxHeight = map[i][j];
			if (map[i][j] < minHeight) minHeight = map[i][j];
		}
	}

	int maxSZ = 1; // 비가 안 올 경우
	for (int h = maxHeight - 1; h >= minHeight; h--)
	{
		for (int i = 0; i < n; i++) memset(&flood[i], 0, n);
		for (int i = 0; i < n; i++) memset(&visited[i], 0, n);
		raining(h);

		int curSZ = 0;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (!flood[i][j] && !visited[i][j])
					curSZ += bfs(i, j);

		if (maxSZ < curSZ) maxSZ = curSZ;
	}
	printf("%d\n", maxSZ);

	return 0;
}