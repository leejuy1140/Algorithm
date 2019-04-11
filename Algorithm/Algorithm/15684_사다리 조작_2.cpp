#include <stdio.h>

const int MAX = 35;

int n, h, map[MAX][MAX]; // n: ��, h: ��.

/* ���� map�� i��° ���μ��� ����� i�� ������ �� ��ȯ. */
bool CheckLadder()
{
	// ��� ���μ� i�� ���Ͽ�, ���� Ȯ��.
	for (int i = 1; i <= n; i++)
	{
		int r = 1; // �� �� ���μ����� üũ.
		int c = i;
		while (r <= h)
		{
			if (map[r][c])  // ���� ��ġ�� ��ٸ��� ����.
			{
				if (c >= 2) // ���� ��ٸ�.
				{
					if (map[r][c] == map[r][c - 1])
					{
						c--;
						r++;
						continue;
					}
				}
				if (c < n)  // ������ ��ٸ�.
				{
					if (map[r][c] == map[r][c + 1])
					{
						c++;
						r++;
						continue;
					}
				}
			}
			r++;
		}
		if (c != i) return false; // i�� ����� i�� �ƴ϶� ���� ��ȯ.
	}
	return true;
}

/* ��ٸ��� cnt��ŭ ���� �� ���� ���� ���� ��ȯ. */
bool SetLadder(int r, int c, int cnt)
{
	map[r][c] = map[r][c + 1] = -cnt;

	if (cnt == 1) // ��ٸ� �� ��ġ������, i�� i�� �������� Ȯ��.
	{
		if (CheckLadder()) return true;
		else			   return false;
	}
	
	int j = c + 1;
	for (int i = r; i <= h; i++)
	{
		for (j; j < n; j++)
		{
			// ���� ��ġ�� (������)��ٸ��� ������ ��ġ.
			if (!map[i][j] && !map[i][j + 1])
			{
				bool ret = SetLadder(i, j, cnt - 1);
				map[i][j] = map[i][j + 1] = 0;

				if (ret) return ret;
			}
		}
		j = 1;
	}
	return false;
}

int main()
{
	int m;
	scanf("%d %d %d", &n, &m, &h);
	while (m--)
	{
		int a, b;
		scanf("%d %d", &a, &b);
		map[a][b] = map[a][b + 1] = m + 1;
	}
	if (CheckLadder())
	{
		printf("0");
		return 0;
	}

	// ��ٸ��� ���� �� �ִ� ��� ��ġ�� ���ƺ���.
	for (int k = 1; k <= 3; k++) // ��ٸ� ����.
	{
		for (int i = 1; i <= h; i++)
		{
			for (int j = 1; j < n; j++)
			{
				// ���� ��ġ�� (������)��ٸ��� ������ ��ġ.
				if (!map[i][j] && !map[i][j + 1])
				{
					bool ret = SetLadder(i, j, k);
					map[i][j] = map[i][j + 1] = 0;

					if (ret) { printf("%d", k); return 0; }
				}
			}
		}
	}
	printf("-1");

	return 0;
}