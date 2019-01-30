#include <stdio.h>
#include <algorithm>
using namespace std;

const int MAX = 1000;

int main()
{
	int n, m; // За, ї­
	scanf("%d %d", &n, &m);

	int map[MAX][MAX], dp[MAX][MAX];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			scanf("%d", &map[i][j]);

	dp[0][0] = map[0][0];
	for (int i = 1; i < m; i++)
		dp[0][i] = dp[0][i - 1] + map[0][i];
	for (int i = 1; i < n; i++)
		dp[i][0] = dp[i - 1][0] + map[i][0];

	for (int i = 1; i < n; i++)
	{
		for (int j = 1; j < m; j++)
			dp[i][j] = map[i][j] + max(dp[i - 1][j], dp[i][j - 1]);
	}
	printf("%d", dp[n - 1][m - 1]);

	return 0;
}