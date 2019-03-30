#include <stdio.h>
#include <string.h>
#include <queue>
using namespace std;

const int MAX = 301;

bool visited[MAX][MAX];
int n, m, map[MAX][MAX];
int dir[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

int adjWaterCounting(int r, int c)
{
	int water = 0;
	for (int i = 0; i < 4; i++)
	{
		int next_r = r + dir[i][0];
		int next_c = c + dir[i][1];
		if (next_r < 0 || next_c < 0 || next_r >= n || next_c >= m) continue;
		if (!map[next_r][next_c]) water++; // 인접한 곳의 물 카운팅
	}
	return water;
}

void melting()
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (map[i][j] < 0) map[i][j] = 0;
}

int bfs(int r, int c)
{
	queue<pair<int, int>> q;
	q.push(pair<int, int>(r, c));
	visited[r][c] = 1;

	int meltCnt = 0;
	while (!q.empty())
	{
		pair<int, int> cur = q.front();
		q.pop();

		// 현재 빙하 녹이기
		int waterCnt = adjWaterCounting(cur.first, cur.second);
		if (map[cur.first][cur.second] <= waterCnt)
		{
			map[cur.first][cur.second] = -1;
			meltCnt++; // 다 녹았으면, 녹은 개수 카운팅
		}
		else map[cur.first][cur.second] -= waterCnt;

		// 인접 빙하 큐에 삽입
		for (int i = 0; i < 4; i++)
		{
			int next_r = cur.first + dir[i][0];
			int next_c = cur.second + dir[i][1];
			if (next_r < 0 || next_c < 0 || next_r >= n || next_c >= m) continue;
			if (!map[next_r][next_c] || visited[next_r][next_c]) continue;
			
			q.push(pair<int, int>(next_r, next_c));
			visited[next_r][next_c] = 1;
		}
	}
	return meltCnt;
}

int main()
{
	int iceCnt = 0;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			scanf("%d", &map[i][j]);
			if (map[i][j]) iceCnt++;
		}
	}

	int year = 0;
	while (iceCnt)
	{
		int isDiv = 0;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				if (!visited[i][j] && map[i][j])
				{
					if (isDiv++) break;
					iceCnt -= bfs(i, j);
				}
			} if (isDiv == 2) break;
		} if (isDiv == 2) break;
		
		year++;
		melting();
		for (int i = 0; i < n; i++) memset(&visited[i], 0, m);
	}
	if(iceCnt) printf("%d\n", year);
	else	   printf("0\n");

	return 0;
}
