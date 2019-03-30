#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	int n;
	scanf("%d", &n);

	vector<int> seq1(n);
	for (int i = 0; i < n; i++)
		scanf("%d", &seq1[i]);

/*
	s1과 그를 뒤집은 문자열 s2의
	최장 공통 부분 수열(LCS)를 구함.
	팰린드롬에서 문자 추가와 삭제를 동치이므로,
	전체 문자열 길이에서 LCS를 빼면, 정답 !
*/

	// seq1을 뒤집은 수열인 seq2 만들기
	vector<int> seq2(n);
	for (int i = n - 1; i >= 0; i--)
		seq2[n - i - 1] = seq1[i];

	// LCS를 구하는 dp 테이블 채우기.
	vector<vector<int>> dp(n, vector<int>(n));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (seq2[i] == seq1[j])
			{
				if (!i || !j) dp[i][j] = 1;
				else	  	  dp[i][j] = dp[i - 1][j - 1] + 1;
			}
			else
			{
				if (!i && !j) dp[i][j] = 0;
				else if (!i)  dp[i][j] = dp[i][j - 1];
				else if (!j)  dp[i][j] = dp[i - 1][j];
				else		  dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
			}
		}
	}
	printf("%d\n", n - dp[n - 1][n - 1]);

	return 0;
}