#include <stdio.h>
#include <cmath>
#include <cstdint>
#include <algorithm>
using namespace std;

const int N_MAX = 1001;
const int M_MAX = 101;

int dist[N_MAX];
uint64_t sum[N_MAX][N_MAX];
uint64_t cache[N_MAX][N_MAX];
uint64_t dp[M_MAX][N_MAX];

int main()
{
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &dist[i]);
	sort(&dist[0], &dist[n + 1]);

	/* sum[i][j]: 1 ~ j���� �������� i ��ġ�� ���� ��, ���� ����. */
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			sum[i][j] = sum[i][j - 1] + abs(dist[j] - dist[i]);

	/* cache[i][j]: i ~ j ���� �������� 1���� ��, �ּ� ��������. */
	for (int i = 1; i <= n; i++)
	{
		for (int j = i + 1; j <= n; j++)
		{
			uint64_t minSum = UINT64_MAX;
			for (int k = i; k <= n; k++)
			{
				uint64_t curSum = sum[k][j] - sum[k][i - 1];
				if (curSum < minSum) minSum = curSum;
			}
			cache[i][j] = minSum;
			if (i == 1) dp[i][j] = minSum;
		}
	}

	/* dp[i][j]: �������� i���� ��, 1 ~ j ������ �ּ� ���� ���� */
	for (int i = 2; i <= m; i++)
	{
		for (int j = i; j <= n; j++)
		{
			// ��� ���� ������ ���� ���� ��.
			if (j == i) dp[i][i] = 0;
			else
			{
				uint64_t minSum = dp[i - 1][j - 1];
				for (int k = j - 2; k >= i; k--) // k ������ ���� �׷�
				{
					uint64_t curSum = dp[i - 1][k] + cache[k + 1][j];
					if (curSum < minSum) minSum = curSum;
				}
				dp[i][j] = minSum;
			}
		}
	}
	printf("%llu\n", dp[m][n]);

	return 0;
}