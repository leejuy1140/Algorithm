#include <stdio.h>

int answer = 999;
int n, m, h, l, map[35][15]; // ��, ��

/* i���� ����� i���� ���� ������, �� ��ȯ. */
bool check()
{
	/* �� ���μ����� ��ٸ��� Ÿ, �� ���� �������� Ȯ��. */
	for (int sero = 1; sero <= m; sero++)
	{
		int r = 1, c = sero, result = 0;
		while (1)
		{
			int flag = 0;
			if (map[r][c] && map[r][c - 1] && c - 1 >= 1) // ���� ���μ�.
				if (map[r][c] == map[r][c - 1]) { r++; c--; flag = 1; }
			if (map[r][c] && map[r][c + 1] && c + 1 <= m) // ������ ���μ�.
				if (map[r][c] == map[r][c + 1]) { r++; c++; flag = 1; }
			if (!flag) r++;

			if (r > n) { result = c; break; }
		}
		if (sero != result) return false;
	}
	return true;
}

void setLadder(int garo, int sero, int cnt)
{
	if (cnt > 3) return;
	if (cnt > answer) return;
	if (check()) answer = answer < cnt ? answer : cnt;

	/* ���� ���μ��� ���� �� �ִ� ��ġ ã��. */
	int rr = garo + 1, cc = sero;
	if (rr > n) { rr = 1; cc++; }

	for (int c = cc; c < m; c++)
	{
		for (int r = rr; r <= n; r++)
		{
			if (!map[r][c] && !map[r][c + 1])
			{
				map[r][c] = map[r][c + 1] = ++l;
				setLadder(r, c, cnt + 1);
				map[r][c] = map[r][c + 1] = 0;
				l--;
			}
		}
		rr = 1;
	}

}

int main()
{
	scanf("%d %d %d", &m, &h, &n);
	for (int i = 1; i <= h; i++)
	{
		int a, b;
		scanf("%d %d", &a, &b);
		map[a][b] = map[a][b + 1] = ++l;
	}
	if (!n || check())
	{
		printf("0\n");
		return 0;
	}

	/* ù ��° ���μ��� ���� �� �ִ� ��ġ ã��. */
	for (int c = 1; c < m; c++)
	{
		if (answer == 1) break;
		for (int r = 1; r <= n; r++)
		{
			if (answer == 1) break;
			if (!map[r][c] && !map[r][c + 1])
			{
				map[r][c] = map[r][c + 1] = ++l;
				setLadder(r, c, 1);
				map[r][c] = map[r][c + 1] = 0;
				l--;
			}
		}
	}
	if (answer == 999) answer = -1;
	printf("%d\n", answer);

	return 0;
}