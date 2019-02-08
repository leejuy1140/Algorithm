#include <stdio.h>
#include <string.h>
#include <utility>
using namespace std;

const int SIZE = 11;

bool visitedCol[SIZE];
int n, answer, chess[SIZE][SIZE];

/* �����ǰ� ������� ����� �Լ� (color: 1 -> ������, 0 -> ���) */
void makeColorBoard(int board[][SIZE], pair<int, int> &size, int color)
{
	/* �߰��� ���� ũ���� ���� ������, flag �÷��α�. */
	int color_c, flag = 0;

	/* ���� ��ü ��� ���� ũ�� ���ϱ�. */
	if (color)
	{
		size.first = size.second = n;
		if (!(n % 2)) // n�� ¦����, ������ �� 1 ���� �� ���� ũ���� �� ����.
		{ size.second = n - 1; flag = 1; }
		color_c = size.second / 2;
	}
	else
	{
		size.first = size.second = n - 1;
		if (!(n % 2)) size.second = n; // n�� ¦����, ���� �� 1 ����.
		else		  flag = 1;		   // Ȧ����, �߰��� ���� ũ���� �� ����.
		color_c = n / 2 - 1;
	}

	for (int color_r = 0; color_r < size.first; color_r++)
	{
		/* �������� ü������ ¦�� ��, 0 �� ���� ����.
		   ������ ü������ Ȧ�� ��, 0 �� ���� ����.   */
		int chess_r = 2 * color_r, chess_c = 0;
		if (!color) chess_r++;

		// ü������ ���� n�� �Ѿ��, �� ���̸�ŭ ���� �̵�.
		if (chess_r >= n)
		{
			chess_c = chess_r - (n - 1);
			chess_r = n - 1;
		}

		int c = color_c;
		if (c < 0) c *= -1;

		while (chess_r >= 0 && chess_c >= 0 && chess_r <= n - 1 && chess_c <= n - 1)
		{
			board[color_r][c] = chess[chess_r][chess_c];
			c++; chess_r--; chess_c++;
		}

		if (flag && !color_c) flag = 0;
		else				  color_c--;
	}

}

int setBishop(int board[][SIZE], pair<int, int> &size, int r, int c, int cnt)
{
	visitedCol[c] = 1;

	for (int i = r + 1; i < size.first; i++)
	{
		for (int j = 0; j < size.second; j++)
		{
			if (board[i][j] == 1 && !visitedCol[j])
			{
				setBishop(board, size, i, j, cnt + 1);
				visitedCol[j] = 0;
			}
		}
	}
	return answer = answer > cnt ? answer : cnt;
}

int main()
{
	int ret1 = 0, ret2 = 0;
	pair<int, int> black_size, white_size;	  // ��, �� ũ��
	int black[SIZE][SIZE], white[SIZE][SIZE]; // ������, ����

	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			scanf("%d", &chess[i][j]);
			black[i][j] = -1;
			white[i][j] = -1;
		}
	}
	makeColorBoard(black, black_size, 1);
	makeColorBoard(white, white_size, 0);

	for (int i = 0; i < black_size.first; i++)
	{
		for (int j = 0; j < black_size.second; j++)
		{
			if (black[i][j] == 1 && !visitedCol[j])
				ret1 = setBishop(black, black_size, i, j, 1);
		}
	}

	answer = 0;
	memset(visitedCol, 0, n);
	for (int i = 0; i < white_size.first; i++)
	{
		for (int j = 0; j < white_size.second; j++)
		{
			if (white[i][j] == 1 && !visitedCol[j])
				ret2 = setBishop(white, white_size, i, j, 1);
		}
	}
	printf("%d\n", ret1 + ret2);

	return 0;

}