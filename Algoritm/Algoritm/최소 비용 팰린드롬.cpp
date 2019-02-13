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
	   아래부터 dp 표 채우기 !
	   1. 정의
	   dp[i][j]: 문자열의 i ~ j 중 팰린드롬을 만들기 위한 최소 비용.
	   2. 점화식
	   if(i == j): 맨 앞과 뒤가 같다면, 가운데 부분의 최소 비용 그대로 !
	   else		 : 맨 앞과 뒤가 다르다면, 왼쪽과 오른쪽의 추가, 삭제 최소값 중 더 작은 값 선택 ! 
				   왼쪽 추가, 삭제 최소값: dp[i][j-1] + j의 추가, 삭제 중 최소값.
				   오른쪽 추가, 삭제 최소값: dp[i+1][j] + i의 추가, 삭제 중 최소값.
	*/
	for (int i = n - 1; i > 0; i--) // 행
	{
		for (int j = i + 1; j <= n; j++) // 열
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