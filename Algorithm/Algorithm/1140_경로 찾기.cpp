#include <iostream>
#include <cstring>
using namespace std;

const int MAX = 101;

bool visited[MAX];
int n, graph[MAX][MAX], answer[MAX][MAX];

/* start에서 시작하여, 연결된 모든 노드는 answer 배열에 1로 표시. */
void dfs(int start, int cur)
{
	visited[cur] = true; // 현재 노드 cur에 방문 체크.
	for (int i = 0; i < n; i++) // 현재 노드 cur에 대하여,
	{
		// 1. 연결 안 된 노드면, 패스.
		// 2. 시작점이 아닌데 방문 했었으면, 패스.
		if (!graph[cur][i]) continue;
		if (visited[i] && i != start) continue;

		dfs(start, i); // i와 연결된 노드 찾으러 감.
		answer[start][i] = 1; // 시작점에서 i는 경로가 있음.
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			scanf("%d", &graph[i][j]);

	for (int i = 0; i < n; i++) // 모든 점에 대하여, 경로 찾기.
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