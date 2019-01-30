#include <stdio.h>

const int MAX = 100;
struct Heap
{
/*
			1
		2       3
	  4   5   6   7

	- data �迭�� �ε����� �켱 ������ ���� ��ġ.
	- �θ� ����� ��ġ�� �ڽ� ����� ��ġ�� 2�� ���� ��!!!
	  (���̰� 1�� ������ �� ���� ����� ���� 2�辿 �����ϱ� ����)
	- 0������ ��� ����.
*/
	int data[MAX];
	int idx = 0;

	void push(int v)
	{
		// 1. �� ���� ���Ҹ� �߰�
		data[++idx] = v;

		// 2. �켱 ������ ����
		// ������ ����� ��ġ�� ��� �ٲ�� ����.
		int newIdx = idx;

		// ������ ����� ��ġ�� ��Ʈ�� ������ �� ����, �켱 ���� ��.
		while (newIdx >= 1)
		{
			// ������ ��尡 �θ𺸴� �켱 ������ ������ �ٲ�
			// �θ� ����� ��ġ�� �ڽ� ��ġ�� / 2 !!!
			if (data[newIdx] < data[newIdx / 2])
			{
				int tmp = data[newIdx];
				data[newIdx] = data[newIdx / 2];
				data[newIdx / 2] = tmp;

				newIdx /= 2;
			}
			else break;
		}
	}

	void pop()
	{
		// ��Ʈ�� ������ ��, �� �� ���Ҹ� ����.
		data[1] = data[idx];
		data[idx] = 0;
		idx--;

		// �Ʒ��� �������鼭, ��Ʈ�� �ö�� ������ ��ġ�� ã��
		int parent = 1;
		while (1)
		{
			// 1. �ڽ� �� �켱 ������ ���� ����� ��ġ�� ����.
			// ���� Ʈ���� �� �� ������ ��ġ�� �ڽ� ���� �ľ� !
			int child = 0;

 			if (parent * 2 > idx) break; // 1-1. �ڽ��� �� �� ���� ���
			else if(parent * 2 + 1 <= idx) // 1-2. �ڽ��� �� �� �ִ� ���
			{
				if (data[parent * 2] < data[parent * 2 + 1]) child = parent * 2;
				else										 child = parent * 2 + 1;
			}
			else child = parent * 2; // 1-3. ���� �ڽĸ� �ִ� ���

			// 2. ���� ���Һ��� �ڽ��� �켱 ������ ������, �ڸ� �ٲ�.
			// �ڽ� ����� ��ġ�� �θ� ��� ��ġ * 2 !!!
			if (data[child] < data[parent])
			{
				int tmp = data[parent];
				data[parent] = data[child];
				data[child] = tmp;

				parent = child;
			}
			else break;
		}
	}

	int top()
	{
		if (idx <= 0) return -1;
		else		  return data[1]; 
	}
};
Heap pq;

void inorderTraversal(int nodeIdx)
{
	if (nodeIdx > pq.idx) return;

	inorderTraversal(nodeIdx * 2); // ��
	printf("%d ", pq.data[nodeIdx]);
	inorderTraversal(nodeIdx * 2 + 1); // ��
}

int main()
{
	pq.push(3); printf("[push 3] top: %d -> ", pq.top()); inorderTraversal(1); printf("\n");
	pq.push(2); printf("[push 2] top: %d -> ", pq.top()); inorderTraversal(1); printf("\n");
	pq.push(1); printf("[push 1] top: %d -> ", pq.top()); inorderTraversal(1); printf("\n");
	pq.push(5); printf("[push 5] top: %d -> ", pq.top()); inorderTraversal(1); printf("\n");
	pq.push(10); printf("[push 10] top: %d -> ", pq.top()); inorderTraversal(1); printf("\n\n");

	pq.pop(); printf("[pop] top: %d -> ", pq.top()); inorderTraversal(1); printf("\n");
	pq.pop(); printf("[pop] top: %d -> ", pq.top()); inorderTraversal(1); printf("\n");
	pq.pop(); printf("[pop] top: %d -> ", pq.top()); inorderTraversal(1); printf("\n");
	pq.pop(); printf("[pop] top: %d -> ", pq.top()); inorderTraversal(1); printf("\n");

	return 0;
}