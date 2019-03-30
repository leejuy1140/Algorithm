#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;

const int MAX = 20020;

int n, m;
vector<int> visited;
vector<vector<int>> graph;

bool dfs(int node, int group)
{
	visited[node] = group;

	int ret = 0;
	for (int i = 0; i < graph[node].size(); i++)
	{
		int adjNode = graph[node][i];
		int adjGroup = group + 1;
		if (adjGroup == 3) adjGroup = 1;

		if (visited[adjNode] == visited[node]) return 1;
		if (!visited[adjNode]) ret = dfs(adjNode, adjGroup);
	}
	return ret;
}

int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d %d", &n, &m);
		graph.clear();   graph.resize(n + 1);
		visited.clear(); visited.resize(n + 1);
		for (int i = 0; i < m; i++)
		{
			int a, b;
			scanf("%d %d", &a, &b);
			graph[a].push_back(b);
			graph[b].push_back(a);
		}
		
		int ret = dfs(1, 1);
		for (int i = 1; i <= n; i++)
			if (!visited[i]) ret += dfs(i, 1);
		if (ret) printf("NO\n");
		else	 printf("YES\n");
	}
	return 0;
}