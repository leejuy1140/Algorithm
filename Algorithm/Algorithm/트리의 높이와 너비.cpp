#include <stdio.h>
#include <vector>
using namespace std;

int n;
vector<vector<int>> tree, level;
// level: 각 레벨 당 노드의 열 번호 저장

int dfs(int node, int lv, int base) // 부모 노드의 열 번호
{
	if (node == -1) return 0;

	int leftCnt = dfs(tree[node][0], lv + 1, base); // 왼쪽 자식 수
	level[lv].push_back(base + leftCnt + 1); // 현재 노드의 열은 부모 노드의 열 + 왼쪽 자식 수
	int rightCnt = dfs(tree[node][1], lv + 1, level[lv].back()); // 오른쪽 자식 수
	return leftCnt + rightCnt + 1; // 총 자식 수 반환.
}

int main()
{
	scanf("%d", &n);
	tree.resize(n + 1);
	level.resize(n + 1);
	for (int i = 0; i < n; i++)
	{
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		tree[a].push_back(b);
		tree[a].push_back(c);
	}
	
	// 루트 노드 구하기
	int root = 1;
	for (root; root <= n; root++)
	{
		int flag = 0;
		for (int i = 1; i <= n; i++)
		{
			if (i == root) continue;

			if (tree[i][0] == root || tree[i][1] == root)
			{ flag = 1; break; } // 누군가의 자식이면, 루트가 아님.
		}
		if (!flag) break;
	}

	// 각 레벨 당 노드의 열 번호 구하기.
	dfs(root, 1, 0);
	
	// 각 레벨 당 너비를 구해, 최대 너비 찾기.
	int maxWidth = 0, maxLevel = 0;
	for (int i = 1; i <= n; i++)
	{
		if (!level[i].size()) continue;
		int width = level[i].back() - level[i][0] + 1;
		if (width > maxWidth)
		{
			maxWidth = width;
			maxLevel = i;
		}
	}
	printf("%d %d\n", maxLevel, maxWidth);

	return 0;
}