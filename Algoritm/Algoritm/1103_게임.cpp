#include <stdio.h>

const int MAX = 51;

char board[MAX][MAX];
int n, m, cache[MAX][MAX]; // ���� ��ġ���� �� �� �ִ� �ִ� ���� Ƚ�� ����.
bool flag, visited[MAX][MAX]; // Ž�� ���� cycle ������, flag set.

inline int max(int a, int b)
{
	return a > b ? a : b;
}

int game(int r, int c)
{
	if (flag)		   return 0;
	if (visited[r][c]) return flag = 1;    // cycle üũ.
	if (cache[r][c])   return cache[r][c]; // �޸������̼�.
	
	visited[r][c] = 1;

	int ret = 1;
	int move = board[r][c] - '0';
	for (int dir = 0; dir < 4; dir++)
	{
		int nr = r;
		int nc = c;
		if		(dir == 0) nr += move;
		else if (dir == 1) nr -= move;
		else if (dir == 2) nc += move;
		else			   nc -= move;

		if (nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
		if (board[nr][nc] == 'H') continue;

		// ���� ��ġ���� ������ �� �ִ� �ִ� Ƚ�� ã��.
		ret = max(ret, game(nr, nc) + 1);
		visited[nr][nc] = 0;
	}
	return cache[r][c] = ret; // Ž�� ���� ����.
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

	game(0, 0);
	if (flag) printf("-1");
	else	  printf("%d", cache[0][0]);

	return 0;
}