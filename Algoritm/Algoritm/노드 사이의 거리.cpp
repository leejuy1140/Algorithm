#include <stdio.h>
#include <vector>
#include <string.h>
using namespace std;

int n, m, tree[1001][1001];
bool chk[1001];

void dfs(int x, int y, int dist)
{
	if (x == y)
	{
		printf("%d\n", dist);
		return;
	}

	chk[x] = 1;
	for (int i = 1; i <= n; i++)
	{
		if (i == x) continue;
		if (!chk[i] && tree[x][i])
		{
			dfs(i, y, dist + tree[x][i]);
			chk[i] = 0;
		}
	}
}

int main()
{
	scanf("%d %d", &n, &m);
	for (int i = 0; i <= n; i++)
		memset(tree[i], 0, sizeof(int) * n + 1);

	for (int i = 0; i < n-1; i++)
	{
		int a, b, d;
		scanf("%d %d %d", &a, &b, &d);
		
		tree[a][b] = d;
		tree[b][a] = d;
	}

	while (m--)
	{
		int x, y;
		scanf("%d %d", &x, &y);
		memset(&chk[0], 0, n + 1);

		dfs(x, y, 0);
	}

	return 0;
}