#include <stdio.h>

const int MAX = 100;
struct Heap
{
/*
			1
		2       3
	  4   5   6   7

	- data 배열의 인덱스는 우선 순위에 따른 위치.
	- 부모 노드의 위치는 자식 노드의 위치를 2로 나눈 값!!!
	  (높이가 1씩 증가할 때 마다 노드의 수가 2배씩 증가하기 때문)
	- 0번지는 사용 안함.
*/
	int data[MAX];
	int idx = 0;

	void push(int v)
	{
		// 1. 맨 끝에 원소를 추가
		data[++idx] = v;

		// 2. 우선 순위를 맞춤
		// 삽입한 노드의 위치는 계속 바뀌기 때문.
		int newIdx = idx;

		// 삽입한 노드의 위치가 루트에 도달할 때 까지, 우선 순위 비교.
		while (newIdx >= 1)
		{
			// 삽입한 노드가 부모보다 우선 순위가 높으면 바꿈
			// 부모 노드의 위치는 자식 위치를 / 2 !!!
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
		// 루트를 삭제한 후, 맨 끝 원소를 넣음.
		data[1] = data[idx];
		data[idx] = 0;
		idx--;

		// 아래로 내려가면서, 루트로 올라온 원소의 위치를 찾음
		int parent = 1;
		while (1)
		{
			// 1. 자식 중 우선 순위가 높은 노드의 위치를 구함.
			// 현재 트리의 맨 끝 원소의 위치로 자식 여부 파악 !
			int child = 0;

 			if (parent * 2 > idx) break; // 1-1. 자식이 둘 다 없는 경우
			else if(parent * 2 + 1 <= idx) // 1-2. 자식이 둘 다 있는 경우
			{
				if (data[parent * 2] < data[parent * 2 + 1]) child = parent * 2;
				else										 child = parent * 2 + 1;
			}
			else child = parent * 2; // 1-3. 왼쪽 자식만 있는 경우

			// 2. 현재 원소보다 자식의 우선 순위가 높으면, 자리 바꿈.
			// 자식 노드의 위치는 부모 노드 위치 * 2 !!!
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

	inorderTraversal(nodeIdx * 2); // 왼
	printf("%d ", pq.data[nodeIdx]);
	inorderTraversal(nodeIdx * 2 + 1); // 오
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