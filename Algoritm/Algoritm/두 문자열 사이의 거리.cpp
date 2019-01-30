#include <stdio.h>
#include <string.h>

const int MAX = 1010;

int dp[MAX][MAX];
char a[MAX], b[MAX];

void initDpTable(int aLen, int bLen)
{
	int flag = 0;
	if (a[0] != b[0]) { dp[0][0] = 2; flag = 2; }
	else                dp[0][0] = 0;

	for (int i = 1; i < aLen; i++)
	{
		if (a[i] == b[0] && flag == 2)
		{
			dp[0][i] = dp[0][i - 1] - 1;
			flag--;
		}
		else dp[0][i] = dp[0][i - 1] + 1;
	}
	for (int i = 1; i < bLen; i++)
	{
		if (a[0] == b[i] && flag == 1)
		{
			dp[i][0] = dp[i - 1][0] - 1;
			flag--;
		}
		else
			dp[i][0] = dp[i - 1][0] + 1;
	}
}

int getMinumum(int i, int j)
{
	int l = dp[i][j - 1];
	int u = dp[i - 1][j];
	int d = dp[i - 1][j - 1];

	if (d < l && d < u) return d + 1;
	else				return l < u ? l : u;
}

int main()
{
	scanf("%s %s", a, b);
	int aLen = strlen(a);
	int bLen = strlen(b);

	initDpTable(aLen, bLen);

	for (int i = 1; i < bLen; i++)
	{
		for (int j = 1; j < aLen; j++)
		{
			if (a[j] == b[i])
				dp[i][j] = dp[i - 1][j - 1];
			else
			{
				int minNum = getMinumum(i, j);
				dp[i][j] = minNum + 1;
			}
		}
	}

	/*for (int i = 0; i < bLen; i++)
	{
		for (int j = 0; j < aLen; j++)
			printf("%d", dp[i][j]);
		printf("\n");
	}*/
	printf("%d", dp[bLen - 1][aLen - 1]);

	return 0;
}