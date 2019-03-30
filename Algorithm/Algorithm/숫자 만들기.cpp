#include <stdio.h>
#include <string.h>

const int M = 3;
const int MAX = 100001;
const int QUOTIENT = 1000007;

int main()
{
	int n;
	scanf("%d", &n);

	int dp[MAX];
	memset(dp, 0, sizeof(int) * (n + 1));

	for (int i = 1; i <= n; i++)
	{
		if (i <= M) dp[i] += 1;
		for (int j = 1; j <= M; j++)
		{
			if (i - j >= 0)       dp[i] += dp[i - j];
			if (dp[i] > QUOTIENT) dp[i] %= QUOTIENT;
		}
	}
	printf("%d\n", dp[n]);

	return 0;
}