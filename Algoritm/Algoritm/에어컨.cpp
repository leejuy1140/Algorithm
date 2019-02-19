#include <stdio.h>
#include <cmath>
#include <algorithm>
#include <climits>
using namespace std;

const int N_MAX = 1001;
const int M_MAX = 101;

int dist[N_MAX]; // 사람 위치
int pos[M_MAX][N_MAX]; // 마지막 에어컨 위치

/* dp[i][j]: 에어컨이 i대일 때,
			 사람 1 ~ j 까지의 최소 불쾌 지수 */
long long dp[M_MAX][N_MAX];

int main()
{
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &dist[i]);
	fill(&dp[1][1], &dp[m + 1][n + 1], LLONG_MAX);
	sort(&dist[0], &dist[n + 1]);

	/* 에어컨이 1대일 때, 불쾌지수 구하기. */
	dp[1][1] = 0;
	pos[1][1] = dist[1];

	for (int j = 2; j <= n; j++)
	{
		for (int p = dist[j]; p >= pos[1][j - 1]; p--)
		{
			long long curSum = 0;
			for (int k = 1; k <= j; k++)
				curSum += abs(dist[k] - p);

			if (dp[1][j] <= curSum) break;

			dp[1][j] = curSum;
			pos[1][j] = p;
		}
	}

	/* 2대 이상일 때, 불쾌지수 구하기. */
	for (int i = 2; i <= m; i++)
	{
		bool flag = 0;
		for (int j = i; j <= n; j++)
		{
			if (j == i) // 사람 수와 에어컨 수가 같을 때.
			{
				dp[i][j] = 0;
				pos[i][j] = j;
			}
			else
			{
				long long minUncomfort = LLONG_MAX;
				for (int k = j - 1; k >= i; k--) // k 까지는 이전 그룹
				{
					long long prevUncomfort = dp[i - 1][k];
					int prevPos = pos[i - 1][k];
					if (prevUncomfort >= minUncomfort) break;

					for (int p = prevPos + 1; p <= dist[j]; p++)
					{
						long long curUncomfort = 0;
						for (int sIdx = k + 1; sIdx <= j; sIdx++)
							curUncomfort += abs(p - dist[sIdx]);

						if (curUncomfort + prevUncomfort >= minUncomfort) break;

						minUncomfort = curUncomfort + prevUncomfort;
						pos[i][j] = p;
					}
				}
				dp[i][j] = minUncomfort;
			}
		}
	}

	if (dp[m][n] == LLONG_MAX) dp[m][n] = 0;
	printf("%lld\n", dp[m][n]);

	return 0;
}