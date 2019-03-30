#include <stdio.h>

const int MAX = 101;
int n, map[MAX][MAX];
long long dp[MAX][MAX];

long long dfs(int r, int c)
{
	if (r == n - 1 && c == n - 1) return 1;
	
	int move = map[r][c];
	if (!move) return 0;

	long long &ret = dp[r][c];
	if (ret != -1) return ret;

	ret = 0;
	for (int i = 0; i < 2; i++)
	{
		int nr = r, nc = c;
		if (!i) nr += move;
		else	nc += move;
		if (nr >= n || nc >= n) continue;
		ret += dfs(nr, nc);
	}
	return ret;
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			scanf("%d", &map[i][j]);
			dp[i][j] = -1;
		}
	}

	long long answer = dfs(0, 0);
	printf("%lld", answer);
	return 0;
}