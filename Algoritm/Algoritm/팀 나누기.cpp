#include <stdio.h>
#include <string.h>
#define MAX 505

int main()
{
	int n, m;
	scanf("%d %d", &n, &m);

	int nameOfGroup = 1;
	int numPerGroup = n / m;
	int data[MAX], dp[MAX][2]; // 0: �׷� ��, 1: �׷� ��
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &data[i]);
		dp[i][0] = nameOfGroup;
		if (nameOfGroup < m && !(i % numPerGroup)) nameOfGroup++;
	}

	int maxData[MAX];
	memset(maxData, 0, sizeof(int) * (n + 1));

	while (1)
	{
		/* �׷��� �� ��� */
		int maxGroupSum = 0; // ������ ���� �׷��� ��
		int maxGroupIdx = 0; // ������ ���� �׷��� ������ �ε���
		for (int i = 1; i <= n; i++)
		{
			if (dp[i - 1][0] == dp[i][0])
				dp[i][1] = dp[i - 1][1] + data[i];
			else
			{
				dp[i][1] = data[i];
				if (dp[i - 1][1] > maxGroupSum)
				{
					maxGroupIdx = i - 1;
					maxGroupSum = dp[i - 1][1];
				}
			}
		}
		if(dp[n][1] > maxGroupSum)
		{
			maxGroupIdx = n;
			maxGroupSum = dp[n][1];
		}

		/*printf("maxIdx: %d, maxSum: %d\n", maxGroupIdx, maxGroupSum);
		for (int i = 1; i <= n; i++)
			printf("[%d] %d\n", dp[i][0], dp[i][1]);
		printf("\n");*/
		
		/* �׷� �ִ� �� ���� */
		if (maxData[maxGroupIdx] == maxGroupSum) break;
		maxData[maxGroupIdx] = maxGroupSum;

		/* ���� ���� ū �׷��� ���ʰ� ������ �� ���� ���� �� �� �׷����� �ѱ�� */
		int leftIdx = maxGroupIdx; // ���� �� �ε��� ã��
		for (leftIdx; leftIdx >= maxGroupIdx - numPerGroup; leftIdx--)
			if (dp[leftIdx][0] != dp[maxGroupIdx][0]) break;
		if (leftIdx < maxGroupIdx - numPerGroup) leftIdx = maxGroupIdx - numPerGroup;

		// ù ��° �׷��̰ų�, �߰� �׷��ε� �������� �� ������, ���������� �ѱ��.
		if ((maxGroupIdx != n && data[maxGroupIdx] < data[leftIdx]) || dp[maxGroupIdx][0] == 1)
			dp[maxGroupIdx][0] = dp[maxGroupIdx + 1][0];
		else
			dp[leftIdx][0] = dp[leftIdx - 1][0];
	}
	
	int answer = 9999999;
	for (int i = 1; i <= n; i++)
		if (maxData[i] && answer > maxData[i]) answer = maxData[i];
	printf("%d\n", answer);

	return 0;
}