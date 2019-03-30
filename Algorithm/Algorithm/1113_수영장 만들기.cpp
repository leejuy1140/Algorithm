#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

const int MAX = 51;
const int FLOOD = -1;

bool fix[MAX][MAX]; // 물 높이 정해진 경우 true로 fix.
int water[MAX][MAX]; // 최대 채울 수 있는 물의 양.
int n, m, map[MAX][MAX];
int dir[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

// 범람한 현재 좌표와 연관된 지역 전부 범람 표시하기.
void Flooding(int r, int c)
{
	bool visited[MAX][MAX];
	memset(visited, false, sizeof(visited));

	queue<pair<int, int>> q;
	q.push(make_pair(r, c));
	visited[r][c] = true;
	water[r][c] = FLOOD;

	while (!q.empty())
	{
		pair<int, int> cur = q.front();
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			int nr = cur.first + dir[i][0];
			int nc = cur.second + dir[i][1];
			if (nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
			if (fix[nr][nc] || visited[nr][nc]) continue;

			if (water[nr][nc]) // 물을 채운 지역이라면, 범람.
			{
				q.push(make_pair(nr, nc));
				visited[nr][nc] = true;
				water[nr][nc] = FLOOD;
			}
		}
	}
}

// 모든 좌표에 대해 물을 waterHeight만큼 채웠을 때, 범람하는지 체크.
void CheckFlood(int r, int c, int waterHeight)
{
	for (int i = 0; i < 4; i++)
	{
		int nr = r + dir[i][0];
		int nc = c + dir[i][1];
		if (nr < 0 || nc < 0 || nr >= n || nc >= m) continue;

		// 현재 좌표에 물을 넣었더니 범람했다면, 주변 전부 범람시키기.
		if (!water[nr][nc] && map[nr][nc] < waterHeight)
		{
			Flooding(r, c);
			break;
		}
	}

	// 범람 안 된 지역 체크하러 가기.
	int rr = r, cc = c + 1;
	while (water[rr][cc] <= 0 || fix[rr][cc])
	{
		if (cc == m - 1)
		{
			rr++;
			cc = 1;
			if (rr == n) return;
		}
		else cc++;
	}
	return CheckFlood(rr, cc, waterHeight);
}

int main()
{
	int maxHeight = 0;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			scanf("%1d", &map[i][j]);
			if (map[i][j] > maxHeight) maxHeight = map[i][j];
		}
	}

	// maxHeight만큼 물 채우면, 범람 여부 확인.
	while (maxHeight)
	{
		// 1. maxHeight만큼 물을 채울 수 있는 곳 채우기.
		int sr = 0, sc = 0;
		for (int i = 1; i < n - 1; i++)
		{
			for (int j = 1; j < m - 1; j++)
			{
				if (fix[i][j]) continue;

				if (map[i][j] < maxHeight)
				{
					water[i][j] = maxHeight - map[i][j];
					if (!sr && !sc) { sr = i; sc = j; }
				}
				else water[i][j] = 0;
			}
		}

		// 2. maxHeight만큼 물을 채웠을 때, 범람하는 지역 체크.
		CheckFlood(sr, sc, maxHeight);

		// 3. 현재 높이에서 범람 안됐다면, fix.
		for (int i = 1; i < n - 1; i++)
			for (int j = 1; j < m - 1; j++)
				if (!fix[i][j] && water[i][j] > 0) fix[i][j] = true;

		maxHeight--;
	}

	int answer = 0;
	for (int i = 1; i < n - 1; i++)
		for (int j = 1; j < m - 1; j++)
			if (fix[i][j]) answer += water[i][j];
	printf("%d", answer);

	return 0;
}