/*
1) ���� ����
1. ������ ���� �ٸ� ������ �� ĭ ����.
2. �� ĭ ��ȯ.
3. ���� ������ �̷���� �ִ� ���� �� ���� �κ� ����.

2) ���� (���� Ž��)
1. ���� ���� �ٸ� ������ �� ĭ dfs�� ����. (��, �� ���� ����.)
2. ���� ��ȯ�� �� ���� �� ���� �κ��� ����.

*/

#include <iostream>
#include <algorithm>
using namespace std;

const int MAX = 51;

int n, answer;
char map[MAX][MAX];
int dir[2][2] = { {1, 0}, {0, 1} }; // �Ʒ�, ������ ĭ�� ��ȯ.


/* ���� ���� ���� �� ������ ���̸� ���ϰ� ���� ����. */
void longestCandyRow(int r)
{
	int eat = 1;
	bool flag = false; // ���� üũ ���̸�, true.
	for (int c = 1; c <= n; c++) // ������ ĭ�� ������ ���, ���信 �ݿ��ϱ� ����.
	{
		if (map[r][c - 1] == map[r][c])
		{
			if (!flag) flag = true;
			eat++;
		}
		else if (flag)
		{
			answer = max(answer, eat);
			flag = false;
			eat = 1;
		}
	}
}

/* ���� ���� ���� �� ������ ���̸� ���ϰ� ���� ����. */
void longestCandyCol(int c)
{
	int eat = 1;
	bool flag = false; // ���� üũ ���̸�, true.
	for (int r = 1; r <= n; r++)  // ������ ĭ�� ������ ���, ���信 �ݿ��ϱ� ����.
	{
		if (map[r - 1][c] == map[r][c])
		{
			if (!flag) flag = true;
			eat++;
		}
		else if (flag)
		{
			answer = max(answer, eat);
			flag = false;
			eat = 1;
		}
	}
}

void selectCandy(int r, int c)
{
	for (int i = 0; i < 2; i++)
	{
		int nr = r + dir[i][0];
		int nc = c + dir[i][1];
		if (nr < 0 || nc < 0 || nr >= n || nc >= n) continue;
		if (map[r][c] == map[nr][nc]) continue; // �ٸ� �� ������ ��ȯ ����.

		swap(map[r][c], map[nr][nc]); // ��ȯ.
		if (i) // ���� ��ȯ -> r, c, nc
		{
			longestCandyRow(r);
			longestCandyCol(c);
			longestCandyCol(nc);
		}
		else    // �¿� ��ȯ -> c, r, nr
		{
			longestCandyCol(c);
			longestCandyRow(r);
			longestCandyRow(nr);
		}
		swap(map[r][c], map[nr][nc]); // ���� ����.
	}

	if (c + 1 < n) return selectCandy(r, c + 1);
	else
	{
		if (r + 1 < n) return selectCandy(r + 1, 0);
		else		   return;
	}
}

int main()
{
	cin >> n;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> map[i][j];

	// +) ó�� ������ ���̰� ���� �� ���� ����.
	for (int i = 0; i < n; i++)
	{
		longestCandyRow(i);
		longestCandyCol(i);
	}

	selectCandy(0, 0);
	cout << answer << endl;
	return 0;
}