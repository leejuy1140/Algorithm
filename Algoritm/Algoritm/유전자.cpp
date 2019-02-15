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
	
	/* dp[i][j]: str[i ~ j] 중 최대 KOI 길이 */
	int len = strlen(str);
	int answer = 0;
	int open = 0, close = 0;
	 
	for (int i = len - 1; i >= 0; i--)
	{
		if (str[i] == 't' || str[i] == 'c')
		{
			// 닫는게 부족했는데, 다시 생기면, 끊기
			if (open >= close)
			{
				answer += dp[i + 1][len - 1];
				len = i + 1;
				open = close = 0;

				//for (int i = 0; i < len; i++) printf("%c", str[i]);
				//printf("[%d] -> %d\n", len, answer);
			}
			close++;
		}
		else open++;

		for (int j = i + 1; j < len; j++)
		{
			if ((str[i] == 'a' && str[j] == 't') || (str[i] == 'g' && str[j] == 'c'))
				dp[i][j] = dp[i + 1][j - 1] + 2;
			else dp[i][j] = max(dp[i][j - 1], dp[i + 1][j]);
		}
	}

	/*for (int i = 0; i < strlen(str); i++)
	{
		for (int j = 0; j < strlen(str); j++)
			printf("%d ", dp[i][j]);
		printf("\n");
	}*/
	printf("%d\n", answer + dp[0][len - 1]);

	return 0;
}