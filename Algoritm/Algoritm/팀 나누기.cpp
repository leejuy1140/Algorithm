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

	/* dp[i][j]: score[1] ~ score[j]�� i���� �׷����� ������ ��,
				 ���� ������ ū �׷��� ����.					 */
	for (int i = 2; i <= m; i++)
	{
		for (int j = i; j <= n; j++)
		{
			/* i���� �л��� i���� �׷����� �����ٸ�,
			   �� �� ���̹Ƿ�, ������ ���� ���� �л� ����. */
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
					/* ������ ���� �׷��� �ִ� ���� �̿���, ���� �ĺ��� �� �� �ִ� �� ���� !
					   - �ٷ� �� �׷��� k��° �л������� �ִ� ���� ������ �л����� �� �׷����� ���� ��,
					     �� �� �ִ� ���� ���� �׷��� ��������� �ִ� �׷� ��.
					   - �� ������ ù ������ ���� ���� �ٷ� �� ������ ���鼭,
					     �ִ� �׷� ���� �ּҰ� �Ǵ� ���� ����.											*/
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