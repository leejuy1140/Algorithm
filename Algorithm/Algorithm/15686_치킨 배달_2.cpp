#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

const int N_MAX = 51;
const int M_MAX = 15;
const int INF = 99999999;

int answer = INF;
int n, m, map[N_MAX][N_MAX];

bool check[M_MAX]; // ġŲ �� ���� ����.
vector<pair<int, int>> store, home;

int GetDistance()
{
	// ������ ������ ���� ����� ġŲ �������� �Ÿ� ���ϱ�.
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
	if (cnt == m) // m�� ���� ��, ġŲ �Ÿ� ���ϱ�.
	{
		answer = min(answer, GetDistance());
		return;
	}

	// ���� ġŲ �� ����.
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

	// m���� ġŲ �� ���� ������.
	for (int i = 0; i < store.size(); i++)
	{
		SelectStore(i, 1);
		check[i] = false;
	}
	printf("%d", answer);

	return 0;
}