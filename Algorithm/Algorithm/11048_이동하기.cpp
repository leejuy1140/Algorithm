#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAX = 1005;

int n, m, map[MAX][MAX], dp[MAX][MAX]; // (i, j) ~ (n, m) 최대 사탕 개수.
int dir[3][2] = { {1, 0}, {0, 1}, {1, 1} };

int dfs(int r, int c)
{
	// (n, m) ~ (n, m)의 최대 사탕 개수는 map[n][m].
	if (r == n && c == m) return map[r][c];

	int &ret = dp[r][c]; // 이전에 계산한 값이 있다면, 반환.
	if (ret != -1) return ret;

	ret = 0; // 없다면, 3가지 경우 중 가장 큰 값 찾아 탐색.
	for (int i = 0; i < 3; i++)
	{
		int nr = r + dir[i][0];
		int nc = c + dir[i][1];
		if (nr < 1 || nc < 1 || nr > n || nc > m) continue;
		ret = max(ret, dfs(nr, nc) + map[r][c]);
	}
	return ret;
}

int main()
{
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf("%d", &map[i][j]);
	memset(dp, -1, sizeof(dp)); // -1로 초기화해야 0개와 구별 가능.
	printf("%d\n", dfs(1, 1));
	return 0;
}