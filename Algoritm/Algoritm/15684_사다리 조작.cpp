#include <stdio.h>

int answer = 999;
int n, m, h, l, map[35][15]; // 행, 열

/* i번의 결과가 i번이 전부 나오면, 참 반환. */
bool check()
{
	/* 각 세로선마다 사다리를 타, 몇 번이 나오는지 확인. */
	for (int sero = 1; sero <= m; sero++)
	{
		int r = 1, c = sero, result = 0;
		while (1)
		{
			int flag = 0;
			if (map[r][c] && map[r][c - 1] && c - 1 >= 1) // 왼쪽 가로선.
				if (map[r][c] == map[r][c - 1]) { r++; c--; flag = 1; }
			if (map[r][c] && map[r][c + 1] && c + 1 <= m) // 오른쪽 가로선.
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

	/* 다음 가로선을 놓을 수 있는 위치 찾기. */
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

	/* 첫 번째 가로선을 놓을 수 있는 위치 찾기. */
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