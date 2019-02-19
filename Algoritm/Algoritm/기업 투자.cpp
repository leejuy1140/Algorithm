#include <stdio.h>
#include <queue>
using namespace std;

const int MONEY_MAX = 305;
const int FIRM_MAX = 25;
 
int info[MONEY_MAX][FIRM_MAX];
int dp[MONEY_MAX][FIRM_MAX];

int main()
{
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++)
	{
		int invest;
		scanf("%d", &invest);
		for(int firm = 1; firm <= m; firm++)
			scanf("%d", &info[invest][firm]);
	}

	/* dp[i][j]: 1 ~ j 회사에 i만큼 투자했을 때, 최대 이익 */
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			// 1. i를 j회사에 전부 투자.
			dp[i][j] = info[i][j];
			
			// 2. i를 이전 회사들 중 최대 이익을 가진 회사에 투자.
			dp[i][j] = max(dp[i][j], dp[i][j - 1]);

			// 3. 이전 회사들에 1 ~ i-1 만큼 투자한 금액에 남은 금액을 j회사에 투자.
			for (int k = 1; k < i; k++)
			{
				int remain = i - k;
				dp[i][j] = max(dp[i][j], dp[k][j - 1] + info[remain][j]);
			}
		}
	}

	printf("%d\n", dp[n][m]);

	return 0;
}