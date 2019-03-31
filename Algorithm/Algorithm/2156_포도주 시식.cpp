#include <stdio.h>
#include <algorithm>
using namespace std;

const int MAX = 10001;
int n, juice[MAX], dp[MAX]; // 0 ~ i 까지 최대 주스 양 저장.

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &juice[i]);

	dp[0] = juice[0];
	dp[1] = juice[0] + juice[1];
	for (int i = 2; i < n; i++)
	{
		int d1 = dp[i - 1];
		int d2 = dp[i - 2] + juice[i];
		int d3 = juice[i - 1] + juice[i];
		if (i - 3 >= 0) d3 += dp[i - 3];

		dp[i] = max(d1, d2);
		dp[i] = max(dp[i], d3);
	}
	printf("%d", dp[n - 1]);

	return 0;
}