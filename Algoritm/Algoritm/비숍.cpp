#include <stdio.h>
#include <string.h>
#include <queue>
using namespace std;

const int SIZE = 11;

int n, board[SIZE][SIZE], route[SIZE][SIZE];
int dir[4][2] = { {-1, -1}, {-1, 1}, {1, -1}, {1, 1} };

/* ��� ��� üũ (set: 1 -> set, 0 -> clear) */
void chkRoute(int r, int c, int bishopCnt, int set)
{
	if (set) route[r][c] = bishopCnt;
	else	 route[r][c] = 0;

	for (int i = 0; i < 4; i++)
	{
		int next_r = r + dir[i][0];
		int next_c = c + dir[i][1];

		while (next_r >= 0 && next_c >= 0 && next_r < n && next_c < n)
		{
			// ����� ���� �� �ִ� ���̸�, ��� üũ.
			if (board[next_r][next_c])
			{
				// set�ε�, �ٸ� ����� ��ο� ��ġ�� ������,
				if (set && !route[next_r][next_c])
					route[next_r][next_c] = bishopCnt; // set

				// clear�ε�, ���� üũ�ߴ� ��θ�,
				if (!set && route[next_r][next_c] == bishopCnt)
					route[next_r][next_c] = 0; // clear
			}
			next_r += dir[i][0];
			next_c += dir[i][1];
		}
	}
}

int answer = 0;
void setBishop(int r, int c, int bishopCnt)
{
	if (r >= n) return;

	for (int set = 1; set >= 0; set--)
	{
		// ��� ����, ��� ǥ��
		chkRoute(r, c, bishopCnt, set);
		if (!set) bishopCnt--;

		// ���� ��ġ ã��
		int next_r = r, next_c = c;
		while (1)
		{
			next_c++;
			if (next_c >= n)
			{
				next_r++;
				next_c = 0;
			}
			if (next_r >= n)
			{
				answer = answer > bishopCnt ? answer : bishopCnt;
				break;
			}
			if (board[next_r][next_c] && !route[next_r][next_c]) break;
		}
		setBishop(next_r, next_c, bishopCnt + 1);
	}
}

int main()
{
	scanf("%d", &n);

	int s_r = -1, s_c = -1;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			scanf("%d", &board[i][j]); // 1: ��� O
			if (board[i][j] && s_r < 0 && s_c < 0)
			{ s_r = i; s_c = j; } // ��� ù �ڸ�
		}
	}

	if (s_r >= 0 && s_c >= 0)
		setBishop(s_r, s_c, 1);
	printf("%d\n", answer);

	return 0;
}