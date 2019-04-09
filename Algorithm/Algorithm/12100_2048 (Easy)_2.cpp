#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAX = 21;
int n, answer, board[MAX][MAX];

/* ���� ���� ��ϳ��� ��ġ�� ��ģ ���� �迭 ũ�� ��ȯ. */
int MergeBlocks(int arr[], int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		if (arr[i] == arr[i + 1]) // �����Ƿ�, ��ħ.
		{
			arr[i] += arr[i + 1];
			for (int j = i + 1; j < size - 1; j++) // ����.
				arr[j] = arr[j + 1];
			size--; // ũ�� ����.
		}
	}
	return size;
}

/* ���� ��ϸ� dir�������� �а�, ��ĥ �� �ִ� ��� ��ġ��. */
void MoveBlocks(int dir)
{
	if (dir == 0) // ��
	{
		int col[MAX];    // ���� ��ϸ� ����.
		for (int c = 0; c < n; c++)
		{
			int idx = 0; // col �迭�� �ε���.
			for (int r = 0; r < n; r++)  // 1. ������ ������� ����.
				if (board[r][c]) col[idx++] = board[r][c];
			idx = MergeBlocks(col, idx); // 2. ���� ��ϳ��� ��ġ��.
			for (int r = 0; r < n; r++)  // 3. ���� ��� ������ ä���.
			{
				if (r < idx) board[r][c] = col[r];
				else		 board[r][c] = 0;
			}
		}
	}
	if (dir == 1) // �Ʒ�
	{
		int col[MAX];
		for (int c = 0; c < n; c++)
		{
			int idx = 0;
			for (int r = n - 1; r >= 0; r--) // �Ʒ�����
				if (board[r][c]) col[idx++] = board[r][c];
			idx = MergeBlocks(col, idx);     // ���� ��ϳ��� ��ġ��.
			for (int r = n - 1; r >= 0; r--) // ���� ��ϸ� �Ʒ��� �̵�.
			{
				if (n - r - 1 < idx) board[r][c] = col[n - r - 1];
				else				 board[r][c] = 0;
			}
		}
	}
	if (dir == 2) // ��
	{
		int row[MAX];
		for (int r = 0; r < n; r++)
		{
			int idx = 0;
			for (int c = 0; c < n; c++)  // ���ʺ���
				if (board[r][c]) row[idx++] = board[r][c];
			idx = MergeBlocks(row, idx); // ���� ��ϳ��� ��ġ��.
			for (int c = 0; c < n; c++)  // ���� ��ϸ� �������� �̵�.
			{
				if (c < idx) board[r][c] = row[c];
				else		 board[r][c] = 0;
			}
		}
	}
	if (dir == 3) // ��
	{
		int row[MAX];
		for (int r = 0; r < n; r++)
		{
			int idx = 0;
			for (int c = n - 1; c >= 0; c--) // �����ʺ���
				if (board[r][c]) row[idx++] = board[r][c];
			idx = MergeBlocks(row, idx);	 // ���� ��ϳ��� ��ġ��.
			for (int c = n - 1; c >= 0; c--) // ���� ��ϸ� ���������� �̵�.
			{
				if (n - c - 1 < idx) board[r][c] = row[n - c - 1];
				else				 board[r][c] = 0;
			}
		}
	}
}

/* 2048 ������ 5ȸ �����ϴ� �Լ�. */
void Do2048(int cnt)
{
	if (cnt == 5) // Ż��: 5ȸ ���� �� �ִ� ��� �� ����.
	{
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				answer = max(answer, board[i][j]);
		return;
	}

	int save[MAX][MAX];					   // 1. ���� ��� ���� ����.
	memcpy(save, board, sizeof(board));
	for (int i = 0; i < 4; i++)			   // 2. 4 ���� �̵�.
	{
		MoveBlocks(i);
		Do2048(cnt + 1);
		memcpy(board, save, sizeof(save)); // 3. ���� ����.
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