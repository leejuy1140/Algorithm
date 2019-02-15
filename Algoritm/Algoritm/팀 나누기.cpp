#include <stdio.h>
#include <string.h>
#include <climits>
#include <algorithm>
using namespace std;

#define MAX 505

int n, m, arr[MAX], sum[MAX];
int dp[MAX][MAX]; // 행, 열 (0: 최적 값, 1: 경계 인덱스)

int main()
{
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &arr[i]);
		sum[i] = sum[i - 1] + arr[i];
	}
	
	/* 0열을 모두 INT_MAX로 초기화 */
	for (int i = 1; i <= n; i++) dp[i][0] = INT_MAX;

	/* dp[i][j]: 1 ~ i까지 j개의 그룹을 만들었을 때, 최적 값 */
	for (int i = 1; i < n + 1; i++)
	{
		for (int j = 1; j < m + 1; j++)
		{
			/* 그룹 수보다 숫자 수가 더 많으면, ? */
			if (i > j)
			{
				int n = INT_MAX;
				for (int k = j; k <= i; k++)
				{
					int ssum, mi;
					if (k >= 2) ssum = sum[i] - sum[k - 1]; // 그룹이 2개 이상이면, 
					else		ssum = sum[i]; //  그룹이 한개라면, sum 그대로.
					
					mi = max(ssum, dp[k - 1][j - 1]);
					
					n = min(n, mi);
					printf("i: %d, j: %d, ssum: %d, mi: %d\n", i, j, ssum, dp[k - 1][j - 1]);
				}
				dp[i][j] = n;
			}

			/* 그룹 수와  숫자 수가 똑같으면, 1 ~ i 까지 중 가장 큰 수가 그룹 내 가장 큰 값. */
			else if (i == j)
			{
				int n = INT_MIN;
				for (int k = 1; k <= i; k++)
					n = max(n, arr[k]);
				dp[i][j] = n;
			}

			/* 그룹 수보다 숫자 수가 적으면, 0으로 채움. */
			else dp[i][j] = 0;
		}
	}

	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
			printf("%d ", dp[j][i]);
		printf("\n");
	}
	printf("%d\n", dp[n][m]);
	
	return 0;
}