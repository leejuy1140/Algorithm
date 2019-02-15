#include <stdio.h>
#include <string.h>
#include <climits>
#include <algorithm>
using namespace std;

#define MAX 505

int n, m, arr[MAX], sum[MAX];
int dp[MAX][MAX]; // ��, �� (0: ���� ��, 1: ��� �ε���)

int main()
{
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &arr[i]);
		sum[i] = sum[i - 1] + arr[i];
	}
	
	/* 0���� ��� INT_MAX�� �ʱ�ȭ */
	for (int i = 1; i <= n; i++) dp[i][0] = INT_MAX;

	/* dp[i][j]: 1 ~ i���� j���� �׷��� ������� ��, ���� �� */
	for (int i = 1; i < n + 1; i++)
	{
		for (int j = 1; j < m + 1; j++)
		{
			/* �׷� ������ ���� ���� �� ������, ? */
			if (i > j)
			{
				int n = INT_MAX;
				for (int k = j; k <= i; k++)
				{
					int ssum, mi;
					if (k >= 2) ssum = sum[i] - sum[k - 1]; // �׷��� 2�� �̻��̸�, 
					else		ssum = sum[i]; //  �׷��� �Ѱ����, sum �״��.
					
					mi = max(ssum, dp[k - 1][j - 1]);
					
					n = min(n, mi);
					printf("i: %d, j: %d, ssum: %d, mi: %d\n", i, j, ssum, dp[k - 1][j - 1]);
				}
				dp[i][j] = n;
			}

			/* �׷� ����  ���� ���� �Ȱ�����, 1 ~ i ���� �� ���� ū ���� �׷� �� ���� ū ��. */
			else if (i == j)
			{
				int n = INT_MIN;
				for (int k = 1; k <= i; k++)
					n = max(n, arr[k]);
				dp[i][j] = n;
			}

			/* �׷� ������ ���� ���� ������, 0���� ä��. */
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