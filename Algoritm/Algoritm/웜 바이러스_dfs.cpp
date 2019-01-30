#include <stdio.h>

const int MAX = 101;

int n, m;
bool visited[MAX];
int myGraph[MAX][MAX];

int cnt = 0;
void dfs(int com)
{
	visited[com] = 1;

	for (int i = 1; i <= n; i++)
	{
		if (myGraph[com][i] && !visited[i])
		{ cnt++; dfs(i); }
	}
}

int main()
{
	scanf("%d\n%d", &n, &m);
	for (int i = 0; i < m; i++)
	{
		int a, b;
		scanf("%d %d", &a, &b);
		myGraph[a][b] = 1;
		myGraph[b][a] = 1;
	}

	dfs(1);
	printf("%d", cnt);

	return 0;
}