#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;

int n, m;
vector<vector<pair<int, int>>> graph;

int daijkstra(int s, int e)
{
	vector<int> dist(n, 9999999); // 최단 거리 저장 벡터

	/* 현재 최단 거리, 노드 (최단 거리가 작은 순으로 나옴) */
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	pq.push(pair<int, int>(0, s));
	dist[s] = 0;

	while (!pq.empty())
	{
		int curNode = pq.top().second;
		int curDist = pq.top().first;
		pq.pop();

		for (int i = 0; i < graph[curNode].size(); i++)
		{
			int nextNode = graph[curNode][i].first;
			int newDist = curDist + graph[curNode][i].second;
			if (dist[nextNode] > newDist)
			{
				dist[nextNode] = newDist;
				pq.push(pair<int, int>(newDist, nextNode));
			}
		}
	}
	return dist[e];
}

int main()
{
	int s, e;
	scanf("%d %d %d %d", &n, &m, &s, &e);
	graph.resize(n);
	for (int i = 0; i < m; i++)
	{
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		graph[a].push_back(make_pair(b, c));
		graph[b].push_back(make_pair(a, c));
	}
	printf("%d", daijkstra(s, e));
	return 0;
}