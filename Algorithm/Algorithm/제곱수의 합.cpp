#include <stdio.h>
#include <cmath>
#include <algorithm>
using namespace std;

const int MAX = 100001;

int main()
{
	int n, dp[MAX];
	scanf("%d", &n);

/*
	Knapsack
	n�� �ּ����� j�� �̿��� ����� !
	(n�� ���� ����, j�� ���� ����, j*j�� ���� ���Զ� ����)
*/

	int maximum = (int)sqrt(n);
	for (int i = 1; i <= n; i++)
	{
		int minNum = 999;
		for (int j = 1; j <= maximum; j++)
		{
			if (j*j > i) break;
			if (j*j == i) { minNum = 1; break; }

			int curNum = dp[j*j] + dp[i - j * j];
			minNum = min(curNum, minNum);
		}
		dp[i] = minNum;
	}
	printf("%d\n", dp[n]);

	return 0;
}