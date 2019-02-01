#include <stdio.h>
#include <vector>
#include <string.h>
using namespace std;

const int MAX = 1001;

int n, m, cnt;
int in[MAX], out[MAX];
bool visited[MAX];

void dfs(vector<vector<int>> &graph, int v, int dir)
{
	visited[v] = 1;
	if (dir) in[v] = ++cnt;

	for (int i = 0; i < graph[v].size(); i++)
	{
		if (!visited[graph[v][i]])
			dfs(graph, graph[v][i], dir);
	}
	if (dir) out[v] = ++cnt;
}

int getMaxIdx()
{
	int maxIdx, maxNum = 0;
	for (int i = 0; i <= n; i++)
	{
		if (!visited[i] && maxNum < out[i])
		{
			maxNum = out[i];
			maxIdx = i;
		}
	}
	return maxIdx;
}

int main() {

	//Please Enter Your Code Here
	scanf("%d %d", &n, &m);
	vector<vector<int>> original(n + 1);
	vector<vector<int>> reverse(n + 1);
	for (int i = 0; i < m; i++)
	{
		int a, b;
		scanf("%d %d", &a, &b);
		original[a].push_back(b);
		reverse[b].push_back(a);
	}
/*
	1. ������ ������ DFS ����.
	(��, �ش� ���� �� time�� �������� time ���)
	2. ������ ������ �ٲ�.
	3. �������� time�� ���� ������� DFS ����.
*/
	
	// �׷����� ��� ����Ǿ� ���� ���� ���� ����.
	for (int i = 1; i <= n; i++)
		if (!visited[i]) dfs(original, i, 1);

	int answer = 0;
	int maxIdx = getMaxIdx();
	memset(visited, 0, n + 1);

	// ������ dfs ����.
	while (out[maxIdx])
	{
		dfs(reverse, maxIdx, 0);
		answer++;

		out[maxIdx] = 0;
		maxIdx = getMaxIdx();
	}
	printf("%d\n", answer);

	return 0;
}