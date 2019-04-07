#include <iostream>
#include <algorithm>
using namespace std;

const int MAX = 1500005;
int n, schedule[MAX][2], dp[MAX]; // i ~ N일까지 최대 이익.

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d %d", &schedule[i][0], &schedule[i][1]);

	for (int i = n; i >= 1; i--)
	{
		// 1. 퇴사일 전에 상담을 못 끝낸다면, 그 전 이익과 동일.
		// 2. 현재 일을 수행하는 것과 안하는 것 중 최대 이익 계산.
		if (i + schedule[i][0] - 1 > n) dp[i] = dp[i + 1];
		else dp[i] = max(dp[i + 1], dp[i + schedule[i][0]] + schedule[i][1]);
	}
	printf("%d", dp[1]);

	return 0;
}