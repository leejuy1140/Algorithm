#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;

int curCnt;
vector<char> visited;

// 나보다 작거나(original) 큰(reverse) 노드 카운팅
void dfs(vector<vector<int>> &graph, int node)
{
	visited[node] = 1;

	for (int i = 0; i < graph[node].size(); i++)
	{
		if (visited[graph[node][i]]) continue;
		dfs(graph, graph[node][i]);
		curCnt++;
	}
}

int main()
{
	int n, m, answer = 0;
	scanf("%d %d", &n, &m);
	visited.resize(n + 1);
	vector<vector<int>> original(n + 1);
	vector<vector<int>> reverse(n + 1);
	for (int i = 0; i < m; i++)
	{
		int a, b;
		scanf("%d %d", &a, &b);
		original[a].push_back(b);
		reverse[b].push_back(a);
	}

	int mid = (n + 1) / 2;
	for (int i = 1; i <= n; i++)
	{
		for (int k = 0; k < 2; k++)
		{
			curCnt = 0;
			memset(&visited[0], 0, n + 1);
			if (!k) dfs(original, i);
			else	dfs(reverse, i);
			if (curCnt >= mid) { answer++; break; }
		}
	}
	printf("%d\n", answer);

	return 0;
}