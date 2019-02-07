#include <stdio.h>
#include <vector>
using namespace std;

int n;
vector<vector<int>> tree, level;
// level: �� ���� �� ����� �� ��ȣ ����

int dfs(int node, int lv, int base) // �θ� ����� �� ��ȣ
{
	if (node == -1) return 0;

	int leftCnt = dfs(tree[node][0], lv + 1, base); // ���� �ڽ� ��
	level[lv].push_back(base + leftCnt + 1); // ���� ����� ���� �θ� ����� �� + ���� �ڽ� ��
	int rightCnt = dfs(tree[node][1], lv + 1, level[lv].back()); // ������ �ڽ� ��
	return leftCnt + rightCnt + 1; // �� �ڽ� �� ��ȯ.
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
	
	// ��Ʈ ��� ���ϱ�
	int root = 1;
	for (root; root <= n; root++)
	{
		int flag = 0;
		for (int i = 1; i <= n; i++)
		{
			if (i == root) continue;

			if (tree[i][0] == root || tree[i][1] == root)
			{ flag = 1; break; } // �������� �ڽ��̸�, ��Ʈ�� �ƴ�.
		}
		if (!flag) break;
	}

	// �� ���� �� ����� �� ��ȣ ���ϱ�.
	dfs(root, 1, 0);
	
	// �� ���� �� �ʺ� ����, �ִ� �ʺ� ã��.
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