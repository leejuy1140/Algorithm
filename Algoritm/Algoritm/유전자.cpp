#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

const int MAX = 505;

char str[MAX];
int dp[MAX][MAX];

int main()
{
	scanf("%s", str);
	int len = strlen(str);
	
	/* dp[r][c]: str[r] ~ str[c]의 최대 부분 서열 */
	for (int r = len - 1; r >= 0; r--)
	{
		for (int c = r + 1; c < len; c++)
		{
			/* 1. aXt 또는 gXc 체크 */
			if ((str[r] == 'a' && str[c] == 't') || (str[r] == 'g' && str[c] == 'c'))
			{
				// X의 최대 부분 서열 + 2
				dp[r][c] = dp[r + 1][c - 1] + 2;
			}

			/* 2. XY 체크 */
			int add = 0;
			for (int k = r; k <= c; k++)
			{
				// str[r] ~ str[c]를 2개로 나눠, 그 합이 가장 큰 값 선택.
				dp[r][c] = max(dp[r][c], dp[r][k] + dp[r + (++add)][c]);
			}

			/* 위의 결과들 중 최대값이 str[r] ~ str[c]의 최대 부분 서열이 되어,
									dp[r][c]에 들어감.							*/
		}
	}
	printf("%d\n", dp[0][len-1]);

	return 0;
}