#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

const int N_MAX = 51;
const int M_MAX = 15;
const int INF = 99999999;

int answer = INF;
int n, m, map[N_MAX][N_MAX];

bool check[M_MAX]; // 치킨 집 선택 여부.
vector<pair<int, int>> store, home;

int GetDistance()
{
	// 각각의 집에서 가장 가까운 치킨 집까지의 거리 구하기.
	int curDist = 0;
	for (int i = 0; i < home.size(); i++)
	{
		int minDist = INF;
		for (int j = 0; j < store.size(); j++)
		{
			if (!check[j]) continue;

			int dist = abs(home[i].first - store[j].first);
			dist += abs(home[i].second - store[j].second);
			minDist = minDist < dist ? minDist : dist;
		}
		curDist += minDist;
	}
	return curDist;
}

void SelectStore(int idx, int cnt)
{
	check[idx] = true;
	if (cnt == m) // m개 선택 후, 치킨 거리 구하기.
	{
		answer = min(answer, GetDistance());
		return;
	}

	// 다음 치킨 집 선택.
	for (int i = idx + 1; i < store.size(); i++)
	{
		SelectStore(i, cnt + 1);
		check[i] = false;
	}
}

int main()
{
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			scanf("%d", &map[i][j]);
			if (map[i][j] == 1)	home.push_back({ i, j });
			if (map[i][j] == 2) store.push_back({ i, j });
		}
	}

	// m개의 치킨 집 고르러 떠나기.
	for (int i = 0; i < store.size(); i++)
	{
		SelectStore(i, 1);
		check[i] = false;
	}
	printf("%d", answer);

	return 0;
}