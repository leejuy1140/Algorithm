#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

const int MAX = 51;
const int FLOOD = -1;

bool fix[MAX][MAX]; // �� ���� ������ ��� true�� fix.
int water[MAX][MAX]; // �ִ� ä�� �� �ִ� ���� ��.
int n, m, map[MAX][MAX];
int dir[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

// ������ ���� ��ǥ�� ������ ���� ���� ���� ǥ���ϱ�.
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

			if (water[nr][nc]) // ���� ä�� �����̶��, ����.
			{
				q.push(make_pair(nr, nc));
				visited[nr][nc] = true;
				water[nr][nc] = FLOOD;
			}
		}
	}
}

// ��� ��ǥ�� ���� ���� waterHeight��ŭ ä���� ��, �����ϴ��� üũ.
void CheckFlood(int r, int c, int waterHeight)
{
	for (int i = 0; i < 4; i++)
	{
		int nr = r + dir[i][0];
		int nc = c + dir[i][1];
		if (nr < 0 || nc < 0 || nr >= n || nc >= m) continue;

		// ���� ��ǥ�� ���� �־����� �����ߴٸ�, �ֺ� ���� ������Ű��.
		if (!water[nr][nc] && map[nr][nc] < waterHeight)
		{
			Flooding(r, c);
			break;
		}
	}

	// ���� �� �� ���� üũ�Ϸ� ����.
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

	// maxHeight��ŭ �� ä���, ���� ���� Ȯ��.
	while (maxHeight)
	{
		// 1. maxHeight��ŭ ���� ä�� �� �ִ� �� ä���.
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

		// 2. maxHeight��ŭ ���� ä���� ��, �����ϴ� ���� üũ.
		CheckFlood(sr, sc, maxHeight);

		// 3. ���� ���̿��� ���� �ȵƴٸ�, fix.
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