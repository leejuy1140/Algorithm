#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAX = 21;
int n, answer, board[MAX][MAX];

/* 같은 숫자 블록끼리 합치고 합친 후의 배열 크기 반환. */
int MergeBlocks(int arr[], int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		if (arr[i] == arr[i + 1]) // 같으므로, 합침.
		{
			arr[i] += arr[i + 1];
			for (int j = i + 1; j < size - 1; j++) // 당기기.
				arr[j] = arr[j + 1];
			size--; // 크기 조정.
		}
	}
	return size;
}

/* 숫자 블록만 dir방향으로 밀고, 합칠 수 있는 블록 합치기. */
void MoveBlocks(int dir)
{
	if (dir == 0) // 위
	{
		int col[MAX];    // 숫자 블록만 저장.
		for (int c = 0; c < n; c++)
		{
			int idx = 0; // col 배열의 인덱스.
			for (int r = 0; r < n; r++)  // 1. 위부터 순서대로 저장.
				if (board[r][c]) col[idx++] = board[r][c];
			idx = MergeBlocks(col, idx); // 2. 같은 블록끼리 합치기.
			for (int r = 0; r < n; r++)  // 3. 숫자 블록 위부터 채우기.
			{
				if (r < idx) board[r][c] = col[r];
				else		 board[r][c] = 0;
			}
		}
	}
	if (dir == 1) // 아래
	{
		int col[MAX];
		for (int c = 0; c < n; c++)
		{
			int idx = 0;
			for (int r = n - 1; r >= 0; r--) // 아래부터
				if (board[r][c]) col[idx++] = board[r][c];
			idx = MergeBlocks(col, idx);     // 같은 블록끼리 합치기.
			for (int r = n - 1; r >= 0; r--) // 숫자 블록만 아래로 이동.
			{
				if (n - r - 1 < idx) board[r][c] = col[n - r - 1];
				else				 board[r][c] = 0;
			}
		}
	}
	if (dir == 2) // 왼
	{
		int row[MAX];
		for (int r = 0; r < n; r++)
		{
			int idx = 0;
			for (int c = 0; c < n; c++)  // 왼쪽부터
				if (board[r][c]) row[idx++] = board[r][c];
			idx = MergeBlocks(row, idx); // 같은 블록끼리 합치기.
			for (int c = 0; c < n; c++)  // 숫자 블록만 왼쪽으로 이동.
			{
				if (c < idx) board[r][c] = row[c];
				else		 board[r][c] = 0;
			}
		}
	}
	if (dir == 3) // 오
	{
		int row[MAX];
		for (int r = 0; r < n; r++)
		{
			int idx = 0;
			for (int c = n - 1; c >= 0; c--) // 오른쪽부터
				if (board[r][c]) row[idx++] = board[r][c];
			idx = MergeBlocks(row, idx);	 // 같은 블록끼리 합치기.
			for (int c = n - 1; c >= 0; c--) // 숫자 블록만 오른쪽으로 이동.
			{
				if (n - c - 1 < idx) board[r][c] = row[n - c - 1];
				else				 board[r][c] = 0;
			}
		}
	}
}

/* 2048 게임을 5회 수행하는 함수. */
void Do2048(int cnt)
{
	if (cnt == 5) // 탈출: 5회 수행 후 최대 블록 값 갱신.
	{
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				answer = max(answer, board[i][j]);
		return;
	}

	int save[MAX][MAX];					   // 1. 현재 블록 상태 저장.
	memcpy(save, board, sizeof(board));
	for (int i = 0; i < 4; i++)			   // 2. 4 방향 이동.
	{
		MoveBlocks(i);
		Do2048(cnt + 1);
		memcpy(board, save, sizeof(save)); // 3. 원상 복구.
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			scanf("%d", &board[i][j]);
	Do2048(0);
	printf("%d", answer);
	return 0;
}