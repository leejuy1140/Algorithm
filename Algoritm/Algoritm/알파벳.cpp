#include <stdio.h>
using namespace std;

const int MAX = 21;

int r, c, answer;
char board[MAX][MAX];
bool alpha[27], visited[MAX][MAX];
int dir[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

int dfs(int x, int y, int cnt)
{
	visited[y][x] = 1;
	alpha[board[y][x] - 'A'] = 1;

	for (int i = 0; i < 4; i++)
	{
		int next_x = x + dir[i][0];
		int next_y = y + dir[i][1];
		if (next_x < 0 || next_y < 0 || next_x >= c || next_y >= r) continue;
		if (alpha[board[next_y][next_x] - 'A']) continue;
		if (visited[next_y][next_x]) continue;

		dfs(next_x, next_y, cnt + 1);
		visited[next_y][next_x] = 0;
		alpha[board[next_y][next_x] - 'A'] = 0;

	}
	answer = answer > cnt ? answer : cnt;
}

int main()
{
	scanf("%d %d", &r, &c);
	for (int i = 0; i < r; i++)
	{
		getchar();
		for (int j = 0; j < c; j++)
			scanf("%1c", &board[i][j]);
	}
	dfs(0, 0, 1);
	printf("%d\n", answer);
	return 0;
}