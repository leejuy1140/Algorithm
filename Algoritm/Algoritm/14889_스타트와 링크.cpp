#include <stdio.h>
#include <vector>
#include <cmath>
using namespace std;

const int MAX = 21;

bool team[MAX];
int n, score[MAX][MAX];

int minDiff = 99999999;
void dfs(int member, int memberCnt)
{
	if (memberCnt == n / 2)
	{
		vector<int> start, link;
		for (int i = 1; i <= n; i++)
		{
			if (team[i]) start.push_back(i);
			else		 link.push_back(i);
		}

		int startTeam = 0, linkTeam = 0;
		for (int i = 0; i < n / 2 - 1; i++)
		{
			for (int j = i + 1; j < n / 2; j++)
			{
				startTeam += (score[start[i]][start[j]] + score[start[j]][start[i]]);
				linkTeam += (score[link[i]][link[j]] + score[link[j]][link[i]]);
			}
		}

		int curDiff = abs(startTeam - linkTeam);
		if (minDiff > curDiff) minDiff = curDiff;
		return;
	}

	for (int i = member + 1; i <= n; i++)
	{
		if (!team[i])
		{
			team[i] = 1;
			dfs(i, memberCnt + 1);
			team[i] = 0;
		}
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			scanf("%d", &score[i][j]);

	for (int i = 1; i <= n / 2; i++)
	{
		if (!team[i])
		{
			team[i] = 1;
			dfs(i, 1);
			team[i] = 0;
		}
	}
	printf("%d\n", minDiff);

	return 0;
}