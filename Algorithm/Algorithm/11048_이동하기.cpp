#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAX = 1005;

int n, m, map[MAX][MAX], dp[MAX][MAX]; // (i, j) ~ (n, m) �ִ� ���� ����.
int dir[3][2] = { {1, 0}, {0, 1}, {1, 1} };

int dfs(int r, int c)
{
	// (n, m) ~ (n, m)�� �ִ� ���� ������ map[n][m].
	if (r == n && c == m) return map[r][c];

	int &ret = dp[r][c]; // ������ ����� ���� �ִٸ�, ��ȯ.
	if (ret != -1) return ret;

	ret = 0; // ���ٸ�, 3���� ��� �� ���� ū �� ã�� Ž��.
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
	memset(dp, -1, sizeof(dp)); // -1�� �ʱ�ȭ�ؾ� 0���� ���� ����.
	printf("%d\n", dfs(1, 1));
	return 0;
}