#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

const int MAP_MAX = 55;

int minDist = 99999999;
vector<char> choosed;
vector<pair<int, int>> store;

bool visited[MAP_MAX][MAP_MAX];
int n, m, map[MAP_MAX][MAP_MAX];
int dir[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

int bfs()
{
	for (int i = 0; i < n; i++) memset(&visited[i], 0, n);

	queue<pair<int, pair<int, int>>> q;
	for (int i = 0; i < store.size(); i++)
		if (choosed[i]) q.push(make_pair(0, store[i]));

	int dist = 0;
	while (!q.empty())
	{
		pair<int, pair<int, int>> cur = q.front();
		q.pop();

		if (map[cur.second.first][cur.second.second] == 1)
			dist += cur.first;

		for (int i = 0; i < 4; i++)
		{
			int nr = cur.second.first + dir[i][0];
			int nc = cur.second.second + dir[i][1];
			if (nr < 0 || nc < 0 || nr >= n || nc >= n) continue;
			if (visited[nr][nc]) continue;

			q.push(make_pair(cur.first + 1, make_pair(nr, nc)));
			visited[nr][nc] = 1;
		}
	}
	return dist;
}

void chooseStore(int sIdx, int cnt)
{
	if (cnt == m)
	{
		int curDist = bfs();
		if (minDist > curDist) minDist = curDist;
		return;
	}

	for (int i = sIdx + 1; i < store.size(); i++)
	{
		choosed[i] = 1;
		chooseStore(i, cnt + 1);
		choosed[i] = 0;
	}
}

int main()
{
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			scanf("%d", &map[i][j]);
			if (map[i][j] == 2) store.push_back(make_pair(i, j));
		}
	}
	choosed.resize(store.size());

	for (int i = 0; i < store.size(); i++)
	{
		choosed[i] = 1;
		chooseStore(i, 1);
		choosed[i] = 0;
	}
	printf("%d\n", minDist);

	return 0;
}