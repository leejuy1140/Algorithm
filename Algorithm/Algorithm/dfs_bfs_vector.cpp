#include <stdio.h>
#include <vector>
#include <queue>
#include <string.h>
#include <algorithm>
using namespace std;

int n, m;
vector<char> visited;
vector<vector<int>> myGraph;

void dfs(int v)
{
	visited[v] = 1;
	printf("%d ", v);

	for (int i = 0; i < myGraph[v].size(); i++)
	{
		if (!visited[myGraph[v][i]])
		{
			dfs(myGraph[v][i]);
			visited[myGraph[v][i]] = 1;
		}
	}
}

void bfs(int v)
{
	queue<int> q;
	q.push(v);
	visited[v] = 1;

	while (!q.empty())
	{
		int cur = q.front();
		printf("%d ", cur);
		q.pop();

		for (int i = 0; i < myGraph[cur].size(); i++)
		{
			if (!visited[myGraph[cur][i]])
			{
				q.push(myGraph[cur][i]);
				visited[myGraph[cur][i]] = 1;
			}
		}
	}
}

int main()
{
	scanf("%d %d", &n, &m);
	myGraph.resize(n + 1);
	visited.resize(n + 1);
	memset(&visited[0], 0, n + 1);

	for (int i = 0; i < m; i++)
	{
		int a, b;
		scanf("%d %d", &a, &b);
		myGraph[a].push_back(b);
		myGraph[b].push_back(a);
	}
	for (int i = 0; i < n; i++) // 작은 노드부터 탐색
		sort(myGraph[i].begin(), myGraph[i].end());

	dfs(0); printf("\n");
	memset(&visited[0], 0, n + 1);
	bfs(0);

	return 0;
}