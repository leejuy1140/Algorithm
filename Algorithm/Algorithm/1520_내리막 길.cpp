#include <stdio.h>

const int MAX = 501;

/*
dp배열을 -1로 초기화하는 이유는
경로가 없는 경우과 방문하지 않은 경로를 구분하지 못하여,
방문 결과 경로가 없는 것임에도 불구하고, 중복 계산이 되기 때문.
해결 1. dp배열을 -1로 초기화.
해결 2. 경로 수를 1부터 시작하고, -1한 값을 출력.
해결 3. 방문 배열을 따로 만들어, 방문 체크.
*/

int n, m, map[MAX][MAX], dp[MAX][MAX];
int dr[4] = { 1, -1, 0, 0 };
int dc[4] = { 0, 0, -1, 1 };

// (r, c)에서 (n-1, m-1)까지 가는 경로의 수 구하기.
int CheckPath(int r, int c)
{
	int &ret = dp[r][c];
	if (ret != -1) return ret;

	ret = 0;
	for (int i = 0; i < 4; i++)
	{
		int nr = r + dr[i];
		int nc = c + dc[i];
		if (nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
		if (map[nr][nc] >= map[r][c]) continue;
		
		if (ret != -1) ret += dp[nr][nc];
		else		   ret += CheckPath(nr, nc);
	}
	return ret;
}

int main()
{
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			scanf("%d", &map[i][j]);
			dp[i][j] = -1;
		}
	}

	dp[n-1][m-1] = 1;
	int answer = CheckPath(0, 0);
	printf("%d\n", answer);
	return 0;
}