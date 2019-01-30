#include <stdio.h>
#include <stdlib.h>

const int MAX = 100;

/* tree[i]: i ���� ���� ���.
tree[i].left: i ���� ���� ����� ���� ��� ��
tree[i].right: i ���� ���� ����� ������ ��� �� */
struct Tree
{
	int left;
	int right;
};
Tree tree[MAX];

void preOrderTraversal(int v);
void inOrderTraversal(int v);
void postOrderTraversal(int v);

int main()
{
	int n;
	scanf("%d", &n);

	int root;
	for (int i = 0; i < n; i++)
	{
		int p, l, r;
		scanf("%d %d %d", &p, &l, &r);

		if (i == 0) root = p;

		tree[p].left = l;
		tree[p].right = r;
	}

	// ��Ʈ ���� v�� ����Ʈ���� ��ȸ
	preOrderTraversal(root); printf("\n");
	inOrderTraversal(root); printf("\n");
	postOrderTraversal(root); printf("\n");

	return 0;
}

void preOrderTraversal(int v)
{
	if (v == -1) return;
	
	printf("%d ", v);
	preOrderTraversal(tree[v].left);
	preOrderTraversal(tree[v].right);
}

void inOrderTraversal(int v)
{
	if (v == -1) return;

	inOrderTraversal(tree[v].left);
	printf("%d ", v);
	inOrderTraversal(tree[v].right);
}

void postOrderTraversal(int v)
{
	if (v == -1) return;

	postOrderTraversal(tree[v].left);
	postOrderTraversal(tree[v].right);
	printf("%d ", v);
}