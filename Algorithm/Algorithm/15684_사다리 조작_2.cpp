#include <stdio.h>

const int MAX = 35;

int n, h, map[MAX][MAX]; // n: 열, h: 행.

/* 현재 map의 i번째 세로선의 결과가 i가 나오면 참 반환. */
bool CheckLadder()
{
	// 모든 세로선 i에 대하여, 전부 확인.
	for (int i = 1; i <= n; i++)
	{
		int r = 1; // 맨 위 가로선부터 체크.
		int c = i;
		while (r <= h)
		{
			if (map[r][c])  // 현재 위치에 사다리가 있음.
			{
				if (c >= 2) // 왼쪽 사다리.
				{
					if (map[r][c] == map[r][c - 1])
					{
						c--;
						r++;
						continue;
					}
				}
				if (c < n)  // 오른쪽 사다리.
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
		if (c != i) return false; // i의 결과가 i가 아니라 거짓 반환.
	}
	return true;
}

/* 사다리를 cnt만큼 놓은 후 정답 가능 여부 반환. */
bool SetLadder(int r, int c, int cnt)
{
	map[r][c] = map[r][c + 1] = -cnt;

	if (cnt == 1) // 사다리 다 설치했으면, i가 i로 나오는지 확인.
	{
		if (CheckLadder()) return true;
		else			   return false;
	}
	
	int j = c + 1;
	for (int i = r; i <= h; i++)
	{
		for (j; j < n; j++)
		{
			// 현재 위치에 (오른쪽)사다리가 없으면 설치.
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

	// 사다리를 놓을 수 있는 모든 위치에 놓아보기.
	for (int k = 1; k <= 3; k++) // 사다리 개수.
	{
		for (int i = 1; i <= h; i++)
		{
			for (int j = 1; j < n; j++)
			{
				// 현재 위치에 (오른쪽)사다리가 없으면 설치.
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