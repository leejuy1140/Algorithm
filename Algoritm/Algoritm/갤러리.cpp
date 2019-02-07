#include <stdio.h>
#include <vector>
using namespace std;

#define INSTALL 1
#define TOGETHER 0

int d, p;
vector<char> visited;
vector<vector<int>> myGraph;

// flag: 1 -> �� ī�޶� ��ġ, 0 -> ��ġ X
int dfs(int node, int flag)
{
	visited[node] = flag + 1;

	int ret = 0;
	for (int i = 0; i < myGraph[node].size(); i++)
	{
		int nextNode = myGraph[node][i];
		if (visited[nextNode] <= 0) // �� �μ��� ī�޶� ��ġ.
		{
			if (flag == INSTALL) // �� �μ��� ���� ��� ����
			{
				int ret1 = 0, ret2 = 0;
				ret1 += dfs(nextNode, TOGETHER); // ���� ����ϴ� ���.
				ret2 += dfs(nextNode, INSTALL);  // ���� ��ġ�ϴ� ���.
				ret += (ret1 < ret2 ? ret1 : ret2);
			}
			else ret += dfs(nextNode, INSTALL); // �� �μ��� ���� ��� X, ���� ��ġ.
		}
	}

	visited[node] = -1; // ���� ��� �湮 ǥ��.
	return ret + flag;  // ���� ��忡 ī�޶� ��ġ������ 1 ��ȯ.
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