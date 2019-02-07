#include <stdio.h>
using namespace std;

/* 상하좌우대각 끝까지 */

const int MAX = 16;

int n, answer, route[MAX][MAX];
int dir[3][2] = { {1, 0}, {1, -1}, {1, 1} };

void chkRoute(int r, int c, int queenCnt, int set)
{
	if (set) route[r][c] = queenCnt;
	else	 route[r][c] = 0;

	for (int i = 0; i < 3; i++)
	{
		int next_r = r + dir[i][0];
		int next_c = c + dir[i][1];
		while (next_c >= 0 && next_r < n && next_c < n)
		{
			if (set  && !route[next_r][next_c])			   route[next_r][next_c] = queenCnt;
			if (!set && route[next_r][next_c] == queenCnt) route[next_r][next_c] = 0;
			next_r += dir[i][0];
			next_c += dir[i][1];
		}
	}
}

void setQueen(int r, int c, int queenCnt)
{
	if (queenCnt > n) { answer++; return; }
	if (c >= n) return;

	for (int set = 1; set >= 0; set--)
	{
		chkRoute(r, c, queenCnt, set);
		if (!set) queenCnt--;

		int next_r = r, next_c = c + 1;
		if (set) { next_r++; next_c = 0; }

		while (next_c < n) // 이번 행에 놓을 수 없으면, 실패.
		{
			if (!route[next_r][next_c]) break;
			next_c++;
		}
		setQueen(next_r, next_c, queenCnt + 1);
	}
}

int main()
{
	scanf("%d", &n);
	setQueen(0, 0, 1);
	printf("%d\n", answer);
	return 0;
}