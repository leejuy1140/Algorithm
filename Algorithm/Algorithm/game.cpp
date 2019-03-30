#include <stdio.h>
#include <algorithm>
#include <utility>
using namespace std;

const int MAX = 1001;

int n, score[MAX];
pair<int, int> dp[MAX][MAX];
/* dp[i][j]: score[i] ~ score[j] 최선을 다한 수빈과 선웅의 점수. 
   T(i, j) = min(T(i, j-1), T(i+1, j))							 */

pair<int, int> game(int s, int e, int turn)
{
	if (s == e)
	{
		if (turn % 2) return dp[s][e] = make_pair(score[s], 0);
		else		  return dp[s][e] = make_pair(0, score[s]);
	}

	pair<int, int> ret1 = dp[s + 1][e];
	pair<int, int> ret2 = dp[s][e - 1];

	if (ret1.first == 0 && ret1.second == 0) ret1 = game(s + 1, e, turn + 1);
	if (ret2.first == 0 && ret2.second == 0) ret2 = game(s, e - 1, turn + 1);

	if (turn % 2) // 수빈 차례라면, 선웅 점수 합의 최소 선택
	{
		if (ret1.second < ret2.second)
			return dp[s][e] = make_pair(ret1.first + score[s], ret1.second);
		else
			return dp[s][e] = make_pair(ret2.first + score[e], ret2.second);
	}
	else
	{
		if (ret1.first < ret2.first)
			return dp[s][e] = make_pair(ret1.first, ret1.second + score[s]);
		else
			return dp[s][e] = make_pair(ret2.first, ret2.second + score[e]);
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &score[i]);

	pair<int, int> result = game(1, n, 1);
	printf("%d %d\n", result.first, result.second);

	return 0;
}