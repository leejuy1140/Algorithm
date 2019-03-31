#include <stdio.h>
#include <vector>
using namespace std;

const int MAX = 5;

vector<int> answer;
int board[MAX][MAX];
int dir[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };


void MakeNumber(int r, int c, int digit, int num)
{
	if (digit == 6) // 6자리가 만들어지면, 중복 체크 후 추가.
	{
		for (int i = 0; i < answer.size(); i++)
			if (answer[i] == num) return;
		answer.push_back(num);
		return;
	}

	for (int i = 0; i < 4; i++)
	{
		int nr = r + dir[i][0];
		int nc = c + dir[i][1];
		if (nr < 0 || nc < 0 || nr >= MAX || nc >= MAX) continue;
		MakeNumber(nr, nc, digit + 1, (num * 10) + board[nr][nc]);
	}
}

int main()
{
	for (int i = 0; i < MAX; i++)
		for (int j = 0; j < MAX; j++)
			scanf("%d", &board[i][j]);

	for (int i = 0; i < MAX; i++)
		for (int j = 0; j < MAX; j++)
			MakeNumber(i, j, 1, board[i][j]);
	printf("%d", answer.size());

	return 0;
}