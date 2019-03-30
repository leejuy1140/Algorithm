#include <stdio.h>
#include <vector>
#include <stack>
#include <string.h>
using namespace std;

const int MAX = 1001;
const int FORWARD = 0;
const int REVERSE = 1;

int n, m;
bool visited[MAX];

stack<int> st;
void dfs(vector<vector<int>> &graph, int v, int dir)
{
	visited[v] = 1;
	
	for (int i = 0; i < graph[v].size(); i++)
	{
		if (!visited[graph[v][i]])
			dfs(graph, graph[v][i], dir);
	}
	if (dir == FORWARD) st.push(v);
}

int main()
{
	scanf("%d %d", &n, &m);
	vector<vector<int>> originalGraph(n + 1);
	vector<vector<int>> reverseGraph(n + 1);
	for (int i = 0; i < m; i++)
	{
		int a, b;
		scanf("%d %d", &a, &b);
		originalGraph[a].push_back(b);
		reverseGraph[b].push_back(a);
	}

	for (int i = 1; i <= n; i++)
	{
		if (!visited[i])
			dfs(originalGraph, i, FORWARD);
	}

	int answer = 0;
	memset(visited, 0, n + 1);
	while (!st.empty())
	{
		int node = st.top();
		st.pop();
		
		if (!visited[node])
		{
			dfs(reverseGraph, node, REVERSE);
			answer++;
		}
	}
	printf("%d\n", answer);

	return 0;
}