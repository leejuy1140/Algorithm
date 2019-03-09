#include <stdio.h>
#include <string.h>
#include <queue>
using namespace std;

const int MAX = 101;
const int TOGETHER = 2;

int n, m;
char map[MAX][MAX];
int visited[MAX][MAX];
vector<pair<int, int>> prisoner;
int dir[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

int bfs()
{
	queue <pair<int, pair<int, int>>> q; // ÁË¼ö ¹øÈ£, ÁÂÇ¥
	q.push(make_pair(0, prisoner[0]));
	q.push(make_pair(1, prisoner[1]));
	visited[prisoner[0].first][prisoner[0].second] = 1;
	visited[prisoner[1].first][prisoner[1].second] = 1;

	int doorCnt = 0;
	int breakCnt = 0; // 3ÀÌ µÇ¸é, ´Ù Å»¿Á.
	while (!q.empty())
	{
		int cur_p = q.front().first;
		int cur_r = q.front().second.first;
		int cur_c = q.front().second.second;
		q.pop();

		if (!cur_r || !cur_c || cur_r == n - 1 || cur_c == m - 1)
		{
			if (cur_p == TOGETHER) return visited[cur_r][cur_c];

			breakCnt += 
			if(breakCnt >=  3) 

			continue;
		}

		for (int i = 0; i < 4; i++)
		{
			int next_r = cur_r + dir[i][0];
			int next_c = cur_c + dir[i][1];
			if (next_r < 0 || next_c < 0 || next_r >= n || next_c >= m) continue;
			if (map[next_r][next_c] == '*') continue;

			if (map[next_r][next_c] == '#')
			{
				if(visited[next_r][next_c])
				q.push(make_pair(cur_p, make_pair(next_r, next_c)));
				visited[next_r][next_c] = visited[cur_r][cur_c] + 1;
			}
			else
				visited[next_r][next_c][cur_p] = visited[cur_r][cur_c][cur_p];
		}
	}

	printf("[0]\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			printf("%d", visited[i][j][0]);
		printf("\n");
	}
	printf("[1]\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			printf("%d", visited[i][j][1]);
		printf("\n");
	}
}

int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d %d", &n, &m);
		for (int i = 0; i < n; i++)
		{
			getchar();
			for (int j = 0; j < m; j++)
			{
				scanf("%1c", &map[i][j]);
				if (map[i][j] == '$')
					prisoner.push_back(make_pair(i, j));
			}
		}

		bfs();

		prisoner.clear();
		memset(visited, 0, sizeof(visited));
	}
	return 0;
}