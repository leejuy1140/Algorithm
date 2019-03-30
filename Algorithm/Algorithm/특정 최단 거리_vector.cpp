#include <stdio.h>
#include <string.h>
#include <climits>
#include <vector>
#include <queue>
using namespace std;

const int MAX = 1001;

int n, m, a, b;
vector<vector<pair<int, int>>> myGraph;

int dijkstra(int s, int d)
{
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	pq.push(pair<int, int>(0, s));
	vector<int> dist(n + 1, INT_MAX);
	dist[s] = 0;

	while (!pq.empty())
	{
		pair<int, int> cur = pq.top();
		pq.pop();
		if (cur.second == d) return cur.first;

		for (int i = 0; i < myGraph[cur.second].size(); i++)
		{
			int nextNode = myGraph[cur.second][i].first;
			int nextWeight = cur.first + myGraph[cur.second][i].second;
			if (dist[nextNode] > nextWeight)
			{
				pq.push(pair<int, int>(nextWeight, nextNode));
				dist[nextNode] = nextWeight;
			}
		}
	}
}

int main()
{
	scanf("%d %d", &n, &m);
	myGraph.resize(n + 1);
	for (int i = 0; i < m; i++)
	{
		int aa, bb, cc;
		scanf("%d %d %d", &aa, &bb, &cc);
		myGraph[aa].push_back(pair<int, int>(bb, cc));
		myGraph[bb].push_back(pair<int, int>(aa, cc));
	}
	scanf("%d %d", &a, &b);

	int samePath = dijkstra(a, b);
	int path1 = dijkstra(1, a) + samePath + dijkstra(b, n);
	int path2 = dijkstra(1, b) + samePath + dijkstra(a, n);
	printf("%d\n", path1 < path2 ? path1 : path2);

	return 0;
}