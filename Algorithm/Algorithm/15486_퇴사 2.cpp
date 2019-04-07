#include <iostream>
#include <algorithm>
using namespace std;

const int MAX = 1500005;
int n, schedule[MAX][2], dp[MAX]; // i ~ N�ϱ��� �ִ� ����.

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d %d", &schedule[i][0], &schedule[i][1]);

	for (int i = n; i >= 1; i--)
	{
		// 1. ����� ���� ����� �� �����ٸ�, �� �� ���Ͱ� ����.
		// 2. ���� ���� �����ϴ� �Ͱ� ���ϴ� �� �� �ִ� ���� ���.
		if (i + schedule[i][0] - 1 > n) dp[i] = dp[i + 1];
		else dp[i] = max(dp[i + 1], dp[i + schedule[i][0]] + schedule[i][1]);
	}
	printf("%d", dp[1]);

	return 0;
}