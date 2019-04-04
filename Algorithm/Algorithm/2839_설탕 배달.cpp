#include <iostream>
using namespace std;

const int MAX = 5001;
const int INF = 9999999;

int n, dp[MAX];

int main()
{
	cin >> n;

	dp[3] = dp[5] = 1;
	for (int i = 6; i <= n; i++)
	{
		int cnt1 = INF, cnt2 = INF;
		if (dp[i - 3]) cnt1 = dp[i - 3] + 1;
		if (dp[i - 5]) cnt2 = dp[i - 5] + 1;
		dp[i] = cnt1 < cnt2 ? cnt1 : cnt2;
	}
	if (!dp[n] || dp[n] == INF) printf("-1");
	else						printf("%d", dp[n]);
	
	return 0;
}