#include <stdio.h>
#include <vector>
using namespace std;

const int MAX = 101;

vector<int> dragon; // 드래곤커브의 방향 저장.
int n, map[MAX][MAX];
int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, -1, 0, 1 }; // -하면, 시계방향 90도.

int main()
{
	scanf("%d", &n);
	while (n--)
	{
		int x, y, d, g;
		scanf("%d %d %d %d", &x, &y, &d, &g);

		// 0세대 드래곤 커브.
		map[y][x] = 1;
		x += dx[d];
		y += dy[d];
		map[y][x] = 1;
		dragon.push_back(d);

		// 방향 수정.
		if (d % 2) { for (int i = 0; i < 4; i++) dx[i] *= -1; }
		else	   { for (int i = 0; i < 4; i++) dy[i] *= -1; }

		// 1 ~ n세대 드래곤 커브.
		for (int i = 1; i <= g; i++)
		{
			int k = dragon.size() - 1;
			for (k; k >= 0; k--)
			{
				// 끝점 기준 +90도 회전한 방향.
				int prev_d = dragon[k];
				int cur_d = prev_d - 1;
				if (cur_d < 0) cur_d = 3;

				// 해당 방향으로 이동.
				x += dx[cur_d];
				y += dy[cur_d];
				map[y][x] = 1;
				dragon.push_back(cur_d);
			}
		}

		// 방향 복구.
		if (d % 2) { for (int i = 0; i < 4; i++) dx[i] *= -1; }
		else	   { for (int i = 0; i < 4; i++) dy[i] *= -1; }
		dragon.clear();
	}

	// 꼭지점 전부 드래곤 커브인 곳의 개수 카운팅.
	int answer = 0;
	for (int i = 0; i < MAX - 1; i++)
	{
		for (int j = 0; j < MAX - 1; j++)
			if (map[i][j] && map[i + 1][j] && map[i][j + 1] && map[i + 1][j + 1])
				answer++;
	}
	printf("%d", answer);
	return 0;
}