#include <stdio.h>

const int MAX = 1001;

int n, m, myGraph[MAX][MAX];
bool visited[MAX];

void dfs(int v)
{
	visited[v] = 1;
	for (int i = 1; i <= n; i++)
	{
		if (!visited[i] && myGraph[v][i])
			dfs(i);
	}
}

int main()
{
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++)
	{
		int a, b;
		scanf("%d %d", &a, &b);
		myGraph[a][b] = 1;
		myGraph[b][a] = 1;
	}

	int answer = 0;
	for (int i = 1; i <= n; i++)
	{
		if (!visited[i])
		{
			dfs(i);
			answer++;
		}
	}
	printf("%d", answer);

	return 0;
}