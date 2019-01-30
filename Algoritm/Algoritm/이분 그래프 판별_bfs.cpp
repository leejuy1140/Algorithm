#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;

int n, m;
vector<int> visited;
vector<vector<int>> myGraph;

bool bfs(int node)
{
	queue<pair<int, int>> q; // node, Group
	q.push(pair<int, int>(node, 1));
	visited[node] = 1;

	while (!q.empty())
	{
		pair<int, int> cur = q.front();
		q.pop();

		int newGroup = cur.second + 1;
		if (newGroup == 3) newGroup = 1;

		for (int i = 0; i < myGraph[cur.first].size(); i++)
		{
			int newNode = myGraph[cur.first][i];

			if (!visited[newNode])
			{
				q.push(pair<int, int>(newNode, newGroup));
				visited[newNode] = newGroup; // bfs는 push와 동시에 방문 체크 !
			}
			else if (visited[newNode] == cur.second)
				return false;
		}
	}
	return true;
}

int main()
{
	int t; scanf("%d", &t);
	while (t--)
	{
		scanf("%d %d", &n, &m);
		visited.clear(); visited.resize(n + 1);
		myGraph.clear(); myGraph.resize(n + 1);
		for (int i = 0; i < m; i++)
		{
			int a, b;
			scanf("%d %d", &a, &b);
			myGraph[a].push_back(b);
			myGraph[b].push_back(a);
		}

		int ret;
		for (int i = 1; i <= n; i++)
		{
			if (!visited[i]) ret = bfs(i);
			if (!ret) { printf("NO\n"); break; }
		}
		if(ret) printf("YES\n");
	}
	return 0;
}