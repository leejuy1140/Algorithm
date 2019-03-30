#include <stdio.h>
#include <queue>
using namespace std;

const int MAX = 101;

int n, m, myGraph[MAX][MAX];
bool visited[MAX];

int bfs(int com)
{
	queue<int> q;
	q.push(com);
	visited[com] = 1;

	int cnt = 0;
	while (!q.empty())
	{
		int cur = q.front();
		q.pop();

		for (int i = 1; i <= n; i++)
		{
			if (myGraph[cur][i] && !visited[i])
			{
				cnt++;
				q.push(i);
				visited[i] = 1;
			}
		}
	}
	return cnt;
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
	printf("%d", bfs(1));
	return 0;
}