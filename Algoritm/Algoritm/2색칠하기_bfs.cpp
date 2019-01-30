#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;

int n, m;
vector<int> visited;
vector<vector<int>> myGraph;

bool bfs(int node)
{
	queue<pair<int, int>> q; // node, color
	q.push(pair<int, int> (node, 1));
	visited[node] = 1;

	while (!q.empty())
	{
		pair<int, int> cur = q.front();
		q.pop();

		int newColor = cur.second + 1;
		if (newColor == 3) newColor = 1;

		for (int i = 0; i < myGraph[cur.first].size(); i++)
		{
			int newNode = myGraph[cur.first][i];
			
			if (!visited[newNode])
			{
				q.push(pair<int, int>(newNode, newColor));
				visited[newNode] = newColor; // bfs는 push와 동시에 방문 체크 !
			}
			else if (visited[newNode] == cur.second)
				return false;
		}
	}
	return true;
}

int main()
{
	scanf("%d %d", &n, &m);
	visited.resize(n);
	myGraph.resize(n);
	for (int i = 0; i < m; i++)
	{
		int a, b;
		scanf("%d %d", &a, &b);
		myGraph[a].push_back(b);
		myGraph[b].push_back(a);
	}
	
	if (bfs(0)) printf("YES");
	else		printf("NO");

	return 0;
}