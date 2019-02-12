#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;

int main()
{
	int n, m, s, e;
	scanf("%d %d %d %d", &n, &m, &s, &e);

	vector<vector<pair<int, int>>> graph(n);
	for (int i = 0; i < m; i++)
	{
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		graph[a].push_back(make_pair(b, c));
		graph[b].push_back(make_pair(a, c));
	}

	vector<int> dist(n, 9999999);
	vector<char> check(n, 0);
	dist[s] = 0;

	for (int i = 0; i < n; i++)
	{
		/* 1. 최단거리 확정 안 된 점들 중, 최소값을 구함. */
		int minValue = 9999999, minIdx = -1;
		for (int j = 0; j < n; j++)
		{
			if (!check[j] && minValue > dist[j])
			{
				minIdx = j;
				minValue = dist[j];
			}
		}
		check[minIdx] = 1; // 최소값을 가진 인덱스 확정
		
		/* 2. 최소값을 가진 노드로부터 뻗어나감. */
		for (int j = 0; j < graph[minIdx].size(); j++)
		{
			int nextNode = graph[minIdx][j].first;
			int newDist = minValue + graph[minIdx][j].second;

			if (!check[nextNode] && newDist < dist[nextNode])
				dist[nextNode] = newDist;
		}
	}
	printf("%d\n", dist[e]);

	return 0;
}