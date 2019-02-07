#include <stdio.h>
#include <vector>
using namespace std;

#define INSTALL 1
#define TOGETHER 0

int d, p;
vector<char> visited;
vector<vector<int>> myGraph;

// flag: 1 -> 새 카메라 설치, 0 -> 설치 X
int dfs(int node, int flag)
{
	visited[node] = flag + 1;

	int ret = 0;
	for (int i = 0; i < myGraph[node].size(); i++)
	{
		int nextNode = myGraph[node][i];
		if (visited[nextNode] <= 0) // 옆 부서에 카메라 설치.
		{
			if (flag == INSTALL) // 현 부서와 같이 사용 가능
			{
				int ret1 = 0, ret2 = 0;
				ret1 += dfs(nextNode, TOGETHER); // 같이 사용하는 경우.
				ret2 += dfs(nextNode, INSTALL);  // 새로 설치하는 경우.
				ret += (ret1 < ret2 ? ret1 : ret2);
			}
			else ret += dfs(nextNode, INSTALL); // 현 부서와 같이 사용 X, 새로 설치.
		}
	}

	visited[node] = -1; // 현재 노드 방문 표시.
	return ret + flag;  // 현재 노드에 카메라 설치했으면 1 반환.
}

int main()
{
	scanf("%d %d", &d, &p);
	myGraph.resize(d);
	visited.resize(d);
	for (int i = 0; i < p; i++)
	{
		int a, b;
		scanf("%d %d", &a, &b);
		myGraph[a].push_back(b);
		myGraph[b].push_back(a);
	}

	int answer = 0;
	for (int i = 0; i < d; i++)
		if (!visited[i]) answer += dfs(i, INSTALL);
	printf("%d\n", answer);

	return 0;
}