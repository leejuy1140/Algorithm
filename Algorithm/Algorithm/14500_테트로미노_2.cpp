#include <iostream>

const int MAX = 501;

bool visited[MAX][MAX];
int n, m, answer, map[MAX][MAX];
int dir[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
int mountain[4][4][2] = { {{0, 0}, {0, 1}, {0, 2}, {1, 1}}, // ㅜ
						  {{1, 0}, {1, 1}, {1, 2}, {0, 1}}, // ㅗ
						  {{0, 0}, {1, 0}, {2, 0}, {1, 1}}, // ㅏ
						  {{0, 1}, {1, 1}, {2, 1}, {1, 0}} }; // ㅓ

/* ㅗ모양 값을 계산하여, 최대 값 갱신. */
void CheckMountain(int r, int c)
{
	for (int i = 0; i < 4; i++)		// 변환 종류.
	{
		int area = 0;
		for (int k = 0; k < 4; k++) // 총 4칸.
		{
			int nr = r + mountain[i][k][0];
			int nc = c + mountain[i][k][1];
			if (nr < 0 || nc < 0 || nr >= n || nc >= m) break;
			area += map[r + mountain[i][k][0]][c + mountain[i][k][1]];
		}
		answer = answer > area ? answer : area;
	}
}

/* (r, c)에서 인접한 4칸을 선택하면, ㅗ빼고 다 만들 수 있음. */
void dfs(int r, int c, int area, int cnt)
{
	if (cnt == 4) // 4칸 선택 완료, 최대값 갱신 후 종료.
	{
		answer = answer > area ? answer : area;
		return;
	}

	visited[r][c] = true;
	for (int i = 0; i < 4; i++) // 인접한 칸 고르기.
	{
		int nr = r + dir[i][0];
		int nc = c + dir[i][1];
		if (nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
		if (visited[nr][nc]) continue;

		dfs(nr, nc, area + map[nr][nc], cnt + 1);
		visited[nr][nc] = false;
	}
}


int main()
{
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			scanf("%d", &map[i][j]);

	// (i, j)에서 시작하여, dfs로 인접한 4블록 만들기.
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			dfs(i, j, map[i][j], 1);
			visited[i][j] = false;
			CheckMountain(i, j);
		}
	}
	printf("%d", answer);

	return 0;
}