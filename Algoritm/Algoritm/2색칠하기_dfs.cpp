#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;

const int MAX = 10000;

int n, m;
vector<int> visited;
vector<vector<int>> graph;
int color[2] = { 1, 2 };

bool dfs(int node, int cIdx)
{
	visited[node] = color[cIdx];

	int ret = 0;
	for (int i = 0; i < graph[node].size(); i++)
	{
		int adjNode = graph[node][i];
		int adjIdx = (cIdx + 1) % 2;
		
		// 인접한 노드에 색이 이미 칠해져 있는데, 나랑 똑같으면 실패.
		if (visited[adjNode] == color[cIdx]) return 1;
		if (!visited[adjNode])				 ret = dfs(adjNode, adjIdx);
	}
	return ret;
}

int main()
{
	scanf("%d %d", &n, &m);
	graph.resize(n);
	visited.resize(n);
	for (int i = 0; i < m; i++)
	{
		int a, b;
		scanf("%d %d", &a, &b);
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	if (dfs(0, 0)) printf("NO");
	else		  printf("YES");

	return 0;
}