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
	
	/* dp[r][c]: str[r] ~ str[c]�� �ִ� �κ� ���� */
	for (int r = len - 1; r >= 0; r--)
	{
		for (int c = r + 1; c < len; c++)
		{
			/* 1. aXt �Ǵ� gXc üũ */
			if ((str[r] == 'a' && str[c] == 't') || (str[r] == 'g' && str[c] == 'c'))
			{
				// X�� �ִ� �κ� ���� + 2
				dp[r][c] = dp[r + 1][c - 1] + 2;
			}

			/* 2. XY üũ */
			int add = 0;
			for (int k = r; k <= c; k++)
			{
				// str[r] ~ str[c]�� 2���� ����, �� ���� ���� ū �� ����.
				dp[r][c] = max(dp[r][c], dp[r][k] + dp[r + (++add)][c]);
			}

			/* ���� ����� �� �ִ밪�� str[r] ~ str[c]�� �ִ� �κ� ������ �Ǿ�,
									dp[r][c]�� ��.							*/
		}
	}
	printf("%d\n", dp[0][len-1]);

	return 0;
}