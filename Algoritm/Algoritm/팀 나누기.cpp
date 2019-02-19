#include <stdio.h>
#include <algorithm>
using namespace std;

#define MAX 505

int dp[MAX][MAX];
int n, m, score[MAX];

int main()
{
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &score[i]);
	
	for (int i = 1; i <= n; i++)
		dp[1][i] = score[i] + dp[1][i - 1];

	/* dp[i][j]: score[1] ~ score[j]를 i개의 그룹으로 나눴을 때,
				 가장 점수가 큰 그룹의 점수.					 */
	for (int i = 2; i <= m; i++)
	{
		for (int j = i; j <= n; j++)
		{
			/* i명의 학생을 i개의 그룹으로 나눈다면,
			   각 한 명씩이므로, 점수가 가장 높은 학생 선택. */
			if (i == j)
			{
				for (int k = 1; k <= i; k++)
					dp[i][j] = max(dp[i][j], score[k]);
			}
			else
			{
				int result = 999999999;
				for (int k = i; k < j; k++)
				{
					/* 이전에 구한 그룹의 최대 값을 이용해, 현재 후보가 될 수 있는 값 선택 !
					   - 바로 전 그룹의 k번째 학생까지의 최대 값과 나머지 학생들을 한 그룹으로 묶을 때,
					     둘 중 최대 값이 현재 그룹의 현재까지의 최대 그룹 값.
					   - 이 과정을 첫 열부터 현재 열의 바로 전 열까지 돌면서,
					     최대 그룹 값이 최소가 되는 값을 선택.											*/
					int candidate = max(dp[i - 1][k], dp[1][j] - dp[1][k]);
					result = min(result, candidate);
				}
				dp[i][j] = result;
			}
		}
	}
	printf("%d\n", dp[m][n]);

	return 0;
}