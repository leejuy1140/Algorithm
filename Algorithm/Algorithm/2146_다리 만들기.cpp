#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

const int MAX = 101;
const int INF = 999999;

int n, map[MAX][MAX];
bool visited[MAX][MAX];
int dr[4] = { 0, 0, -1, 1 };
int dc[4] = { -1, 1, 0, 0 };

/* �� ���� ������ ������ ǥ��. */
void CheckIsland(int r, int c, int num)
{
	map[r][c] = num * -1;

	for (int i = 0; i < 4; i++)
	{
		int nr = r + dr[i];
		int nc = c + dc[i];
		if (nr < 0 || nc < 0 || nr >= n || nc > n) continue;
		if (map[nr][nc] == 1) CheckIsland(nr, nc, num);
	}
}

int CheckDistance(int curIsland)
{
	// ���� ���� ���� ť�� ����.
	queue<pair<int, pair<int, int>>> q; // �Ÿ�, ��ǥ
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (map[i][j] * -1 == curIsland)
			{
				q.push(make_pair(0, make_pair(i, j)));
				visited[i][j] = true;
			}
		}
	}

	while (!q.empty())
	{
		int rr = q.front().second.first;
		int cc = q.front().second.second;
		int curDist = q.front().first;
		q.pop();

		// �ٸ� ���� �����ϸ�, ����.
		if (map[rr][cc] < 0 && map[rr][cc] != (curIsland * -1))
			return curDist - 1;

		for (int i = 0; i < 4; i++)
		{
			int nr = rr + dr[i];
			int nc = cc + dc[i];
			if (nr < 0 || nc < 0 || nr >= n || nc >= n) continue;
			if (visited[nr][nc]) continue;

			q.push(make_pair(curDist + 1, make_pair(nr, nc)));
			visited[nr][nc] = true;
		}
	}
	return INF;
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			scanf("%d", &map[i][j]);

	// 1. dfs�� ���� ���� �ٸ� ������ ǥ��.
	int islandCnt = 0; // �� ����
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (map[i][j] > 0) CheckIsland(i, j, ++islandCnt);

	// 2. �� ������ bfs�� �ٸ� ������ �̵� �Ÿ� ���.
	//    �̸� ���� ������ŭ �ݺ��Ͽ�, ���� ª�� �Ÿ� ����.
	int answer = INF;
	for (int k = 0; k < islandCnt; k++)
	{
		int ret = CheckDistance(k + 1);
		answer = answer < ret ? answer : ret;
		memset(visited, false, sizeof(visited));
	}
	printf("%d", answer);

	return 0;
}