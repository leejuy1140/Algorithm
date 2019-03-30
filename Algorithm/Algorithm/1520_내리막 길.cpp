#include <stdio.h>

const int MAX = 501;

/*
dp�迭�� -1�� �ʱ�ȭ�ϴ� ������
��ΰ� ���� ���� �湮���� ���� ��θ� �������� ���Ͽ�,
�湮 ��� ��ΰ� ���� ���ӿ��� �ұ��ϰ�, �ߺ� ����� �Ǳ� ����.
�ذ� 1. dp�迭�� -1�� �ʱ�ȭ.
�ذ� 2. ��� ���� 1���� �����ϰ�, -1�� ���� ���.
�ذ� 3. �湮 �迭�� ���� �����, �湮 üũ.
*/

int n, m, map[MAX][MAX], dp[MAX][MAX];
int dr[4] = { 1, -1, 0, 0 };
int dc[4] = { 0, 0, -1, 1 };

// (r, c)���� (n-1, m-1)���� ���� ����� �� ���ϱ�.
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