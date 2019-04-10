#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

const int MAX = 10;
const int WALL = 1;
const int VIRUS = 2;

bool visited[MAX][MAX];
int n, m, answer, map[MAX][MAX];
int dir[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

/* 바이러스가 퍼진 후 안전 영역의 크기 반환. */
int GetSafeArea()
{
	// 1. 바이러스 위치 큐에 삽입.
	queue<pair<int, int>> q;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (map[i][j] == VIRUS)
			{
				q.push({ i, j });
				visited[i][j] = true;
			}
		}
	}

	// 2. 바이러스 확산.
	while (!q.empty())
	{
		pair<int, int> cur = q.front();
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			int nr = cur.first + dir[i][0];
			int nc = cur.second + dir[i][1];
			if (nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
			if (map[nr][nc] == WALL) continue;
			if (visited[nr][nc]) continue;

			q.push({ nr, nc });
			visited[nr][nc] = true;
		}
	}

	// 3. 안전 영역 계산 후 방문 배열 초기화.
	int safeArea = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (!visited[i][j] && !map[i][j]) safeArea++;
			visited[i][j] = false;
		}
	}
	return safeArea;
}

void SetWall(int r, int c, int cnt)
{
	if (cnt == 3) // 벽 3개 세웠으면, 안전 영역 구하기
	{
		int ret = GetSafeArea();
		answer = answer > ret ? answer : ret;
		return;
	}

	int j = c + 1; // 다음 위치에 벽 세우기.
	for (int i = r; i < n; i++)
	{
		for (j; j < m; j++)
		{
			if (!map[i][j])
			{
				map[i][j] = WALL;
				SetWall(i, j, cnt + 1);
				map[i][j] = 0;
			}
		}
		j = 0;
	}
}

int main()
{
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			scanf("%d", &map[i][j]);

	// 빈 공간에 벽 세우기.
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (!map[i][j])
			{
				map[i][j] = WALL;
				SetWall(i, j, 1);
				map[i][j] = 0;
			}
		}
	}
	printf("%d", answer);

	return 0;
}