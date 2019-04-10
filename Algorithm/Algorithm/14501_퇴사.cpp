#include <iostream>
#include <algorithm>
using namespace std;

const int MAX = 20;
int n, schedule[MAX][2], dp[MAX]; // [0]: 소요일, [1]: 이익.

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d %d", &schedule[i][0], &schedule[i][1]);

	for (int i = n; i >= 1; i--)
	{
		if (i + schedule[i][0] - 1 >= n + 1) dp[i] = dp[i + 1];
		else dp[i] = max(dp[i + 1], dp[i + schedule[i][0]] + schedule[i][1]);
	}
	printf("%d", dp[1]);

	return 0;
}