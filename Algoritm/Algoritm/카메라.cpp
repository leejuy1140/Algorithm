#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

#define INSTALL 1
#define TOGETHER 0

int d, p, newCam;
vector<char> visited;
vector<vector<int>> myGraph;

// flag: 1 -> 새 카메라 설치, 0 -> 설치 필요 X
int dfs(int node, int flag)
{
	visited[node] = flag + 1;

	int ret = 0;
	for (int i = 0; i < myGraph[node].size(); i++)
	{
		int nextNode = myGraph[node][i];
		if (visited[nextNode] <= 0)
		{
			if (flag == INSTALL)
			{
				int ret1 = 0, ret2 = 0;
				ret1 += dfs(nextNode, TOGETHER);
				ret2 += dfs(nextNode, INSTALL);
				ret += min(ret1, ret2);
			}
			else
			{
				ret += dfs(nextNode, INSTALL);
			}
		}
	}
	visited[node] = -1; // 방문은 했기 때문에 -1로 표시
	return ret + flag; // 현재 
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

	int curCam = 0;
	for (int i = 0; i < d; i++)
		if(!visited[i]) curCam += dfs(i, INSTALL);
	printf("%d\n", curCam);

	return 0;
}