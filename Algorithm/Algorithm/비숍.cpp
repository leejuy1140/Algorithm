#include <stdio.h>
#include <string.h>
#include <utility>
using namespace std;

const int SIZE = 11;

bool visitedCol[SIZE];
int n, answer, chess[SIZE][SIZE];

/* 검정판과 흰색판을 만드는 함수 (color: 1 -> 검정색, 0 -> 흰색) */
void makeColorBoard(int board[][SIZE], pair<int, int> &size, int color)
{
	/* 중간에 같은 크기의 열이 있으면, flag 올려두기. */
	int color_c, flag = 0;

	/* 판의 전체 행과 열의 크기 구하기. */
	if (color)
	{
		size.first = size.second = n;
		if (!(n % 2)) // n이 짝수면, 검정판 열 1 감소 및 같은 크기의 열 존재.
		{ size.second = n - 1; flag = 1; }
		color_c = size.second / 2;
	}
	else
	{
		size.first = size.second = n - 1;
		if (!(n % 2)) size.second = n; // n이 짝수면, 흰판 열 1 증가.
		else		  flag = 1;		   // 홀수면, 중간에 같은 크기의 열 존재.
		color_c = n / 2 - 1;
	}

	for (int color_r = 0; color_r < size.first; color_r++)
	{
		/* 검정판은 체스판의 짝수 행, 0 열 부터 시작.
		   흰판은 체스판의 홀수 행, 0 열 부터 시작.   */
		int chess_r = 2 * color_r, chess_c = 0;
		if (!color) chess_r++;

		// 체스판의 행이 n을 넘어가면, 그 차이만큼 열로 이동.
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
	pair<int, int> black_size, white_size;	  // 행, 열 크기
	int black[SIZE][SIZE], white[SIZE][SIZE]; // 검정판, 흰판

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