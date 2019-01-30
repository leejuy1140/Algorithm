#include <stdio.h>
#include <algorithm>
using namespace std;

const int NUM = 3;
const int MAX = 100000;

int n, button[MAX][NUM], sum[MAX][NUM];

int getMaxSumIdx(int i, int j)
{
	int idx;
	if (j == 0)
	{
		if (sum[i - 1][1] > sum[i - 1][2]) return idx = 1;
		else							   return idx = 2;
	}
	if (j == 1)
	{
		if (sum[i - 1][0] > sum[i - 1][2]) return idx = 0;
		else							   return idx = 2;
	}
	if (j == 2)
	{
		if (sum[i - 1][0] > sum[i - 1][1]) return idx = 0;
		else							   return idx = 1;
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < NUM; j++)
		{
			scanf("%d", &button[i][j]);
			if (i == 0) sum[i][j] = button[i][j];
		}
	}

/*
	sum[i][j] = num[i][j] + max(sum[i-1][j-1], sum[i-1][j-2])
	                                      ↑ j가 아닌 버튼 ↑
	                (연속으로 같은 버튼을 누를 수 없기 때문)
*/

	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < NUM; j++)
		{
			int idx = getMaxSumIdx(i, j);
			sum[i][j] = sum[i - 1][idx] + button[i][j];
		}
	}

	int answer = max(sum[n - 1][0], sum[n - 1][1]);
	answer = max(answer, sum[n - 1][2]);
	printf("%d\n", answer);

	return 0;
}