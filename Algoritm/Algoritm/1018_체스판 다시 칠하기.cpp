#include <stdio.h>
#include <algorithm>

const int MAX = 51;
int n, m, board[MAX][MAX];

int solution(int r, int c)
{
	char prev1, prev2;
	int cnt1 = 0, cnt2 = 0;
	for (int i = r; i < r + 8; i++)
	{
		for (int j = c; j < c + 8; j++)
		{
			if (i == r && j == c)
			{ prev1 = 'W'; prev2 = 'B'; }

			if (board[i][j] == prev1) cnt1++;
			if (board[i][j] == prev2) cnt2++;
			std::swap(prev1, prev2);
		}
		std::swap(prev1, prev2);
	}
	return std::min(cnt1, cnt2);
}

int main()
{
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++)
	{
		getchar();
		for (int j = 0; j < m; j++)
			scanf("%1c", &board[i][j]);
	}

	int answer = 99999999;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (i + 7 >= n || j + 7 >= m) continue;
			int ret = solution(i, j);
			answer = std::min(answer, ret);
		}
	}
	printf("%d", answer);
	return 0;
}