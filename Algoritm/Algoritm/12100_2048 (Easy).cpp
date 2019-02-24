#include <stdio.h>
#include <string.h>

const int MAX = 21;

int n, maxNum, board[MAX][MAX];
int direction[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

/* dir �������� ���带 �� ���� ������ ��� �� */
void getLimit(int _dir, int &_si, int &_ei, int &_ii, int &_sj, int &_ej, int &_jj)
{
	if (_dir == 0)	   // ��
	{
		_si = n - 1; _ei = 0; _ii = -1;
		_sj = 0;	 _ej = n; _jj = 1;
	}
	else if (_dir == 1) // ��
	{
		_si = 0; _ei = n - 1; _ii = 1;
		_sj = 0; _ej = n;	  _jj = 1;
	}
	else if (_dir == 2) // ��
	{
		_si = 0;	 _ei = n; _ii = 1;
		_sj = n - 1; _ej = 0; _jj = -1;
	}
	else			   // ��
	{
		_si = 0; _ei = n;	  _ii = 1;
		_sj = 0; _ej = n - 1; _jj = 1;
	}
}

/* ������ �� �� �Ǵ� ���� dir �������� ��. */
void pushToDir(int _dir, int _i, int _j)
{
	int num[MAX], idx = 0, zero = 0;
	memset(num, 0, sizeof(int) * n);

	if (_dir == 0)	   // ��
	{
		for (int i = 0; i < n; i++)
		{
			if (board[i][_j]) num[idx++] = board[i][_j];
			else			  zero++;
		}
		for (int i = 0; i < zero; i++) board[i][_j] = 0;
		for (int i = 0; i < idx; i++) board[i + zero][_j] = num[i];
	}
	else if (_dir == 1) // ��
	{
		for (int i = 0; i < n; i++)
			if (board[i][_j]) num[idx++] = board[i][_j];
		for (int i = 0; i < idx; i++) board[i][_j] = num[i];
		for (int i = idx; i < n; i++) board[i][_j] = 0;
	}
	else if (_dir == 2) // ��
	{
		for (int j = 0; j < n; j++)
		{
			if (board[_i][j]) num[idx++] = board[_i][j];
			else			 zero++;
		}
		for (int j = 0; j < zero; j++) board[_i][j] = 0;
		for (int j = 0; j < idx; j++) board[_i][zero + j] = num[j];
	}
	else			   // ��
	{
		for (int j = 0; j < n; j++)
			if (board[_i][j]) num[idx++] = board[_i][j];
		for (int j = 0; j < idx; j++) board[_i][j] = num[j];
		for (int j = idx; j < n; j++) board[_i][j] = 0;
	}
}

void do2048(int dir, int cnt)
{
	if (cnt == 0) return;

	/* 1. �ش� ������, ��� �� ��谪 ���ϱ�. */
	int si, ei, sj, ej, ii, jj;
	getLimit(dir, si, ei, ii, sj, ej, jj);

	/* 2. �� ���� ���� ���� �ش� �������� �б�. */
	for (int i = 0; i < n; i++)
	{
		if (dir >= 2) pushToDir(dir, i, -1);
		else		 pushToDir(dir, -1, i);
	}

	bool visited[MAX][MAX]; // ������ ��� üũ��
	for (int i = 0; i < n; i++) memset(&visited[i], 0, n);

	/* 3. ���������� ��ġ��. */
	for (int i = si; i != ei; i += ii)
	{
		for (int j = sj; j != ej; j += jj)
		{
			/* ���� ������ ������ ��� üũ. */
			int ni = i + direction[dir][0];
			int nj = j + direction[dir][1];
			if (ni < 0 || ni >= n || nj < 0 || nj >= n) continue;

			/* ���� ���� ����� ���� ���� ������ ������ ���� ������,
			   ��ġ�� ���� ��� ��ġ�� 0 ó��.						 */
			if (board[i][j] == board[ni][nj] && !visited[i][j])
			{
				board[i][j] += board[ni][nj];
				board[ni][nj] = 0;
				visited[i][j] = 1;
				if (board[i][j] > maxNum) maxNum = board[i][j];

				pushToDir(dir, i, j); // �� ���� ���� �б�.
			}
		}
	}

	/* 4. ���� ���� ���� ���� */
	int curBoard[MAX][MAX];
	for (int i = 0; i < n; i++)
		memcpy(&curBoard[i], &board[i], sizeof(int) * n);

	/* 5. ���� ���� ���ؼ�, ���.
		  ���ƿ���, ����� ���� ���·� �ǵ���. */
	for (int i = 0; i < 4; i++)
	{
		do2048(i, cnt - 1);
		for (int k = 0; k < n; k++)
			memcpy(&board[k], &curBoard[k], sizeof(int) * n);
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			scanf("%d", &board[i][j]);
			if (board[i][j] > maxNum) maxNum = board[i][j];
		}
	}

	int oriBoard[MAX][MAX]; // ó�� ���� ����
	for (int i = 0; i < n; i++)
		memcpy(&oriBoard[i], &board[i], sizeof(int) * n);

	/* ���� ������ i. */
	for (int i = 0; i < 4; i++)
	{
		do2048(i, 5);
		for (int k = 0; k < n; k++)
			memcpy(&board[k], &oriBoard[k], sizeof(int) * n);
	}
	printf("%d\n", maxNum);

	return 0;
}