#include <stdio.h>
#include <climits>
#include <vector>
#include <queue>
using namespace std;

vector<int> dijkstra(vector<vector<pair<int, int>>> &town, int s)
{
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	vector<int> dist(town.size(), INT_MAX);
	pq.push(pair<int, int>(0, s));
	dist[s] = 0;

	while (!pq.empty())
	{
		pair<int, int> cur = pq.top();
		pq.pop();

		for (int i = 0; i < town[cur.second].size(); i++)
		{
			int nextHome = town[cur.second][i].first;
			int nextDist = cur.first + town[cur.second][i].second;
			if (nextDist < dist[nextHome])
			{
				dist[nextHome] = nextDist;
				pq.push(pair<int, int>(nextDist, nextHome));
			}
		}
	}
	return dist;
}

int main()
{
	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);
	vector<vector<pair<int, int>>> forward(n + 1), reverse(n + 1);
	for (int i = 0; i < m; i++)
	{
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		forward[a].push_back(pair<int, int>(b, c));
		reverse[b].push_back(pair<int, int>(a, c));
	}

	/*
		단방향 그래프이기 때문에,
		파티에서 각각의 집까지 돌아가는 길은 다익스트라 한 번이면 되지만,
		각각의 집에서 파티로 가는 길은 집들의 수 만큼 다익스트라를 돌려야한다.

		보다 효율적인 방법으로 역방향 그래프를 이용하면,
		각각의 집에서 파티로 가는 길을 다익스트라 한 번만에 구할 수 있다 !!!
	*/

	vector<int> toParty = dijkstra(reverse, k);
	vector<int> toHome = dijkstra(forward, k);
	
	int answer = 0;
	for (int i = 1; i <= n; i++)
	{
		if(toParty[i] + toHome[i] > answer)
			answer = toParty[i] + toHome[i];
	}
	printf("%d\n", answer);

	return 0;
}