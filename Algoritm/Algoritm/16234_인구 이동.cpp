#include <iostream>
#include <cstring>
#include <cmath>
#include <queue>
using namespace std;

const int MAX = 50;

int n, l, r, map[MAX][MAX], team[MAX][MAX];
int dir[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

/* 연합을 이루는지 체크. */
bool isTeam(int a, int b)
{
	if (abs(a - b) >= l && abs(a - b) <= r) return true;
	return false;
}

/* 국경 체크 후, 인국 이동 후의 인구 수 반환. */
int bfs(int r, int c, int teamNum)
{
	queue<pair<int, int>> q;
	q.push(make_pair(r, c));
	team[r][c] = teamNum;

	int totalCnt = 1;		  // 현재 연합 수.
	int totalPop = map[r][c]; // 현재 연합의 총 인구 수.
	
	while (!q.empty())
	{
		pair<int, int> cur = q.front();
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			int nr = cur.first + dir[i][0];
			int nc = cur.second + dir[i][1];
			if (nr < 0 || nc < 0 || nr >= n || nc >= n) continue;
			if (team[nr][nc]) continue;

			if (isTeam(map[nr][nc], map[cur.first][cur.second]))
			{
				q.push(make_pair(nr, nc));
				totalCnt++;
				totalPop += map[nr][nc];
			}
		}
	}

	if (totalCnt == 1)
	{
		team[r][c] = 0;
		return 0;
	}
	return totalPop / totalCnt;
}

int main()
{
	scanf("%d %d %d", &n, &l, &r);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			scanf("%d", &map[i][j]);

	int time = 0;
	while (1)
	{
		/* 국경 체크. */
		int teamNum = 1;	 // 연합 번호
		vector<int> teamPop; // 연합 인구 수
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (!team[i][j])
				{
					int curTeamPop = bfs(i, j, teamNum);
					if (curTeamPop)
					{
						teamPop.push_back(curTeamPop);
						teamNum++;
					}
				}
			}
		}
		if (teamNum == 1) break;

		/* 인구 이동 수행. */
		time++;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (team[i][j]) map[i][j] = teamPop[team[i][j] - 1];

		/* 국경선 닫음. */
		for (int i = 0; i < n; i++)
			memset(&team[i], 0, sizeof(int) * n);
	}
	printf("%d\n", time);

	return 0;
}