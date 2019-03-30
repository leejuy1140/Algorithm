#include <stdio.h>
#include <vector>
using namespace std;

#define VISIT 1
#define CCTV 2

int d, p, answer;
vector<char> visited;
vector<vector<int>> tree;

int dfs(int node) // CCTV ��ġ ���� ��ȯ
{
	visited[node] = VISIT; // dfs �� �ٽ� ���ƿ��� �ʱ� ����, �湮 ǥ��.

	int flag = 0; // �ڽ� �� CCTV ���� �ְ� ������, �÷��� �ø�.
	for (int i = 0; i < tree[node].size(); i++)
	{
		int childNode = tree[node][i];
		if (visited[childNode]) continue;

		/* ���� cctv�� ���Ե��� �ʴ� �ڽ��� �ϳ��� �ִٸ�,
		   ���� ��忡 ī�޶� ��ġ !						 */
		if (dfs(childNode) != CCTV) flag = 1;
	}

	if (flag) // �ڽ� �߿� CCTV ���� �ڽ��� ������,
	{
		answer++; // CCTV ��ġ
		visited[node] = CCTV; // CCTV ��� ǥ��

		for (int i = 0; i < tree[node].size(); i++) // ��� �ڽĵ� CCTV ���.
		{
			int childNode = tree[node][i];
			if (visited[childNode] != CCTV) visited[childNode] = CCTV;
		}
	}
	return visited[node]; // ���� ����� ���� ��ȯ
}

int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		answer = 0;
		scanf("%d %d", &d, &p);
		tree.resize(d);
		visited.resize(d);
		for (int i = 0; i < p; i++)
		{
			int a, b;
			scanf("%d %d", &a, &b);
			tree[a].push_back(b);
			tree[b].push_back(a);
		}

		for (int i = 0; i < d; i++)
		{
			if (!tree[i].size()) { answer++; continue; } // ����� ��尡 ������, ���� ��ġ.
			
			if (visited[i] != CCTV) // ����� ��尡 �ְ� ��ġ �ȵ�����, ��ġ�Ϸ� ���.
				if(dfs(i) != CCTV) answer++; // �ڽĵ��� �� ��ġ�ƴµ� ���� �ȵ� ���, ��ġ.
		}
		printf("%d\n", answer);

		tree.clear();
		visited.clear();
	}
	return 0;
}