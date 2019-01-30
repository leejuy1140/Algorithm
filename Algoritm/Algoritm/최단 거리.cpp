#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;

/*
	가중치가 1인 그래프의 최단 경로 구하기 !
	BFS
*/

int n, m, s, d;
vector<char> visited;
vector<vector<int>> myGraph;

int bfs(int sNode)
{
	queue<pair<int, int>> q;
	q.push(pair<int, int> (sNode, 0));
	visited[sNode] = 1;

	while (!q.empty())
	{
		pair<int, int> cur = q.front();
		q.pop();

		if (cur.first == d) return cur.second;

		for (int i = 0; i < myGraph[cur.first].size(); i++)
		{
			int nextNode = myGraph[cur.first][i];
			if (visited[nextNode]) continue;
			
			q.push(pair<int, int>(nextNode, cur.second + 1));
			visited[nextNode] = 1;
		}
	}
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
	scanf("%d %d", &s, &d);
	
	printf("%d", bfs(s));

	return 0;
}