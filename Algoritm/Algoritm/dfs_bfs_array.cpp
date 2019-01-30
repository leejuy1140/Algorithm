#include <stdio.h>
#include <vector>
#include <queue>
#include <string.h>
using namespace std;

const int MAX = 1001;

int n, m;
bool visited[MAX];
int myGraph[MAX][MAX];

void dfs(int v)
{
	visited[v] = 1;
	printf("%d ", v);

	for (int i = 0; i < n; i++)
		if (myGraph[v][i] && !visited[i]) dfs(i);
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

		for (int i = 0; i < n; i++)
		{
			if (myGraph[cur][i] && !visited[i])
			{
				q.push(i);
				visited[i] = 1;
			}
		}
	}
}

int main()
{
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++)
		memset(&myGraph[i], 0, sizeof(int) * (n + 1));

	for (int i = 0; i < m; i++)
	{
		int a, b;
		scanf("%d %d", &a, &b);
		myGraph[a][b] = 1;
		myGraph[b][a] = 1;
	}

	dfs(0); printf("\n");
	memset(visited, 0, n + 1);
	bfs(0);

	return 0;
}