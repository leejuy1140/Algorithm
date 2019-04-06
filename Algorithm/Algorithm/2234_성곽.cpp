#include <iostream>
#include <queue>
using namespace std;

const int MAX = 51;

int room[MAX * MAX];  // 인덱스: 방 번호, 값: 크기.
int castle[MAX][MAX]; // 방마다 숫자로 체크.
int n, m, map[MAX][MAX];
int dir[4][2] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0} }; // 서북동남(1248)

/* 같은 방을 체크하고 방의 크기 반환. */
int CheckRoom(int r, int c, int num)
{
	queue<pair<int, int>> q;
	q.push(make_pair(r, c));
	castle[r][c] = num;

	int area = 1;
	while (!q.empty())
	{
		int rr = q.front().first;
		int cc = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			if (map[rr][cc] & (1 << i)) continue; // 벽이면 패스.

			int nr = rr + dir[i][0];
			int nc = cc + dir[i][1];
			if (nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
			if (castle[nr][nc]) continue;

			q.push(make_pair(nr, nc));
			castle[nr][nc] = num;
			area++;
		}
	}
	return area;
}

int main()
{
	scanf("%d %d", &m, &n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			scanf("%d", &map[i][j]);
	
	// bfs를 돌며, 방의 개수와 가장 큰 방의 크기 찾기.
	int num = 0;	 // 방의 개수.
	int maxArea = 0; // 가장 큰 방의 크기.
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (!castle[i][j])
			{
				num++;
				room[num] = CheckRoom(i, j, num);
				maxArea = maxArea > room[num] ? maxArea : room[num];
			}
		}
	}

	// 인접한 두 방의 크기를 합한 값 중 가장 큰 값 찾기.
	int maxMergeArea = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (castle[i][j] != castle[i][j + 1]) // 좌우 인접.
			{
				int curArea = room[castle[i][j]] + room[castle[i][j + 1]];
				maxMergeArea = maxMergeArea > curArea ? maxMergeArea : curArea;
			}
			if (castle[i][j] != castle[i + 1][j]) // 상하 인접.
			{
				int curArea = room[castle[i][j]] + room[castle[i + 1][j]];
				maxMergeArea = maxMergeArea > curArea ? maxMergeArea : curArea;
			}
		}
	}
	printf("%d\n%d\n%d", num, maxArea, maxMergeArea);

	return 0;
}