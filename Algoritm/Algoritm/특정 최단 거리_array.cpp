#include <stdio.h>
#include <string.h>
#include <climits>
#include <vector>
#include <queue>
using namespace std;

const int MAX = 801;

int n, m, a, b;
int myGraph[MAX][MAX];

int dijkstra(int s, int d)
{
	priority_queue< pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > pq;
	pq.push(pair<int, int>(0, s));
	vector<int> dist(n + 1, INT_MAX);
	dist[s] = 0;

	while (!pq.empty())
	{
		pair<int, int> cur = pq.top();
		pq.pop();
		if (cur.second == d) return cur.first;

		for (int i = 0; i <= n; i++)
		{
			if (!myGraph[cur.second][i]) continue;

			int nextWeight = dist[cur.second] + myGraph[cur.second][i];
			if (dist[i] > nextWeight)
			{
				pq.push(pair<int, int>(nextWeight, i));
				dist[i] = nextWeight;
			}
		}
	}
	return dist[d];
}

int main()
{
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++)
	{
		int aa, bb, cc;
		scanf("%d %d %d", &aa, &bb, &cc);
		myGraph[aa][bb] = cc;
		myGraph[bb][aa] = cc;
	}
	scanf("%d %d", &a, &b);

	int samePath = dijkstra(a, b);
	long long path1 = (long long)dijkstra(1, a) + (long long)samePath + (long long)dijkstra(b, n);
	long long path2 = (long long)dijkstra(1, b) + (long long)samePath + (long long)dijkstra(a, n);

	long long ans = path1 < path2 ? path1 : path2;
	if (ans >= INT_MAX) ans = -1;
	printf("%lld\n", ans);

	return 0;
}