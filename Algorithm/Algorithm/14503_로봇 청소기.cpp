#include <stdio.h>

const int MAX = 51;

bool visited[MAX][MAX];
int n, m, map[MAX][MAX];
int dir[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} }; // �ϵ�����.

int dfs(int _r, int _c, int _d, int _cnt)
{
	// 1. �������� ȸ���ϸ�, ȸ�� ������ �� ã��.
	int nd = _d;
	for (int i = 0; i < 4; i++)
	{
		nd--;
		if (nd < 0) nd = 3;

		int nr = _r + dir[nd][0];
		int nc = _c + dir[nd][1];
		if (map[nr][nc] || visited[nr][nc]) continue;
		
		visited[nr][nc] = true;
		return dfs(nr, nc, nd, _cnt + 1);
	}

	// 2. 4 ���� ���� û���� �� ������, ����.
	// 3. ������ �� ������, ����.
	int nr = _r - dir[_d][0];
	int nc = _c - dir[_d][1];
	if (map[nr][nc]) return _cnt;
	return dfs(nr, nc, _d, _cnt);
}

int main()
{
	int r, c, d;
	scanf("%d %d", &n, &m);
	scanf("%d %d %d", &r, &c, &d);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			scanf("%d", &map[i][j]);

	// 1. ���� ��ġ û��.
	visited[r][c] = true;
	int ret = dfs(r, c, d, 1);
	printf("%d", ret);

	return 0;
}