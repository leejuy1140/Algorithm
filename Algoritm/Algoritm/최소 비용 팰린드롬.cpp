#include <stdio.h>
#include <string.h>
#include <utility>
using namespace std;

#define MAX 1001
#define min(a, b) (a < b ? a : b)

char str[MAX];
int n, m, dp[MAX][MAX];
pair<int, int> cost[MAX];

int main()
{
	scanf("%d %d", &n, &m);
	getchar(); scanf("%s", str);
	for (int i = 0; i < m; i++)
	{
		char c; getchar(); scanf("%c", &c);
		scanf("%d %d", &cost[c - 'a'].first, &cost[c - 'a'].second);
	}

	/*
	   �Ʒ����� dp ǥ ä��� !
	   1. ����
	   dp[i][j]: ���ڿ��� i ~ j �� �Ӹ������ ����� ���� �ּ� ���.
	   2. ��ȭ��
	   if(i == j): �� �հ� �ڰ� ���ٸ�, ��� �κ��� �ּ� ��� �״�� !
	   else		 : �� �հ� �ڰ� �ٸ��ٸ�, ���ʰ� �������� �߰�, ���� �ּҰ� �� �� ���� �� ���� ! 
				   ���� �߰�, ���� �ּҰ�: dp[i][j-1] + j�� �߰�, ���� �� �ּҰ�.
				   ������ �߰�, ���� �ּҰ�: dp[i+1][j] + i�� �߰�, ���� �� �ּҰ�.
	*/
	for (int i = n - 1; i > 0; i--) // ��
	{
		for (int j = i + 1; j <= n; j++) // ��
		{
			char ci = str[i - 1];
			char cj = str[j - 1];
			
			if (ci != cj)
			{
				int left = dp[i][j - 1] + min(cost[cj - 'a'].first, cost[cj - 'a'].second);
				int up = dp[i + 1][j] + min(cost[ci - 'a'].first, cost[ci - 'a'].second);
				dp[i][j] = min(left, up);
			}
			else dp[i][j] = dp[i + 1][j - 1];
		}
	}
	printf("%d\n", dp[1][n]);
	return 0;
}