#include <stdio.h>
#include <string.h>
#include <vector>
#include <stack>

#define MAX 100001
#define FORWARD 1
#define REVERSE 2

using namespace std;

int n, m, memberCnt, visited[MAX];

stack<int> st;
vector<vector<int>> originalGraph, reverseGraph;

void dfs(vector<vector<int>> &graph, int v, int dir)
{
	visited[v] = dir;
	if (dir == REVERSE) memberCnt++;

	for (int i = 0; i < graph[v].size(); i++)
	{
		if (visited[graph[v][i]] != dir)
			dfs(graph, graph[v][i], dir);
	}
	if (dir == FORWARD) st.push(v);
}

int main()
{
	scanf("%d", &n);
	originalGraph.resize(n + 1);
	reverseGraph.resize(n + 1);

	int noTeamCnt = 0; // 팀 없는 학생 수
	for (int i = 1; i <= n; i++)
	{
		int a; scanf("%d", &a);
		originalGraph[i].push_back(a);
		reverseGraph[a].push_back(i);

		// 초기엔 혼자 팀하고 싶은 학생이 아니면, 팀 없는 학생으로 카운팅
		if (i != a) noTeamCnt++;
	}

	for (int i = 1; i <= n; i++)
	{
		if (visited[i] != FORWARD)
			dfs(originalGraph, i, FORWARD);
	}

	while (!st.empty())
	{
		int num = st.top();
		st.pop();

		if (visited[num] != REVERSE)
		{
			memberCnt = 0; // 한 팀의 멤버 수
			dfs(reverseGraph, num, REVERSE);
			if (memberCnt > 1) noTeamCnt -= memberCnt;
		}
	}
	printf("%d\n", noTeamCnt);

	return 0;
}