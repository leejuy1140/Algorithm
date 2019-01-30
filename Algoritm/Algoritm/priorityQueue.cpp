#include <stdio.h>

const int MAX = 100;
struct myPQ
{
	int data[MAX];
	int idx = -1;

	void push(int v)
	{
		if (idx >= MAX) printf("Overflow\n");
		else data[++idx] = v;
	}

	void pop()
	{
		if (idx < 0) printf("Underflow\n");
		else
		{
			// �켱������ ���� ���� ���Ҹ� ã��
			int highest = 0;
			for (int i = 0; i <= idx; i++)
				if (data[i] > data[highest]) highest = i;

			// �ش� ���Ҹ� ������ ��, �� ���ҵ��� ������ ���.
			data[highest] = 0;
			for (int i = highest; i < idx; i++)
				data[i] = data[i + 1];
			idx--;
		}
	}

	int top()
	{
		if (idx < 0) printf("NULL\n");
		else
		{
			int highest = 0;
			for (int i = 0; i <= idx; i++)
				if (data[i] > data[highest]) highest = i;
			return data[highest];
		}
	}
};

int main()
{
	myPQ pq;
	pq.push(1);
	pq.push(8);
	pq.push(7);
	pq.push(5);
	printf("%d\n", pq.top()); // 8

	pq.pop();
	printf("%d\n", pq.top()); // 7

	pq.pop();
	printf("%d\n", pq.top()); // 5

	pq.pop();
	printf("%d\n", pq.top()); // 1

	return 0;
}