#include <iostream>
#include <cstring>
using namespace std;

const int MAX = 101;

bool visited[MAX];
int n, graph[MAX][MAX], answer[MAX][MAX];

/* start���� �����Ͽ�, ����� ��� ���� answer �迭�� 1�� ǥ��. */
void dfs(int start, int cur)
{
	visited[cur] = true; // ���� ��� cur�� �湮 üũ.
	for (int i = 0; i < n; i++) // ���� ��� cur�� ���Ͽ�,
	{
		// 1. ���� �� �� ����, �н�.
		// 2. �������� �ƴѵ� �湮 �߾�����, �н�.
		if (!graph[cur][i]) continue;
		if (visited[i] && i != start) continue;

		dfs(start, i); // i�� ����� ��� ã���� ��.
		answer[start][i] = 1; // ���������� i�� ��ΰ� ����.
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			scanf("%d", &graph[i][j]);

	for (int i = 0; i < n; i++) // ��� ���� ���Ͽ�, ��� ã��.
	{
		dfs(i, i);
		memset(visited, 0, sizeof(visited));
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			printf("%d ", answer[i][j]);
		printf("\n");
	}
	return 0;
}