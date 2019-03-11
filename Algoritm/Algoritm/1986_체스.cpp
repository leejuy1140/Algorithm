#include <stdio.h>

const int SIZE = 1010;
const int COUNT = 101;

int n, m, board[SIZE][SIZE];
int qcnt, qr[COUNT], qc[COUNT];
int kcnt, kr[COUNT], kc[COUNT];

int qdr[8] = { -1, 1, 0, 0, -1, -1, 1, 1 };
int qdc[8] = { 0, 0, -1, 1, -1, 1, -1, 1 };
int kdr[8] = { -1, -2, -2, -1, 1, 2, 1, 2 };
int kdc[8] = { -2, -1, 1, 2, -2, -1, 2, 1 };

int main()
{
	int pcnt;
	scanf("%d %d", &n, &m);
	scanf("%d", &qcnt);
	for (int i = 0; i < qcnt; i++)
		scanf("%d %d", &qr[i], &qc[i]);
	scanf("%d", &kcnt);
	for (int i = 0; i < kcnt; i++)
		scanf("%d %d", &kr[i], &kc[i]);
	scanf("%d", &pcnt);
	for (int i = 0; i < pcnt; i++)
	{
		int a, b;
		scanf("%d %d", &a, &b);
		board[a - 1][b - 1] = 2;
	}

	for (int i = 0; i < kcnt; i++) // 킹 이동 범위 체크.
	{
		board[kr[i] - 1][kc[i] - 1] = 2;
		for (int dir = 0; dir < 8; dir++)
		{
			int r = kr[i] - 1 + kdr[dir];
			int c = kc[i] - 1 + kdc[dir];
			if (r < 0 || c < 0 || r >= n || c >= m) continue;
			if (board[r][c] == 2) continue;
			if (board[r][c]) continue;
			board[r][c] = 1;
		}
	}
	for (int i = 0; i < qcnt; i++) // 퀸 이동 범위 체크.
	{
		for (int dir = 0; dir < 8; dir++)
		{
			int r = qr[i] - 1;
			int c = qc[i] - 1;
			while (1)
			{
				board[r][c] = 1;
				r += qdr[dir];
				c += qdc[dir];
				if (r < 0 || c < 0 || r >= n || c >= m) break;
				if (board[r][c] == 2) break;
				if (board[r][c]) continue;
			}
		}
	}

	int safeCnt = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (!board[i][j]) safeCnt++;
	printf("%d", safeCnt);
	return 0;
}