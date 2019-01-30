#include <stdio.h>

const int ARRMAX = 10;

struct Queue
{
	int data[ARRMAX];
	int capacity;
	int f, r, cnt;

	void create(int size)
	{
		capacity = size;
		f = 0; r = 0; cnt = 0;
	}
	void push(int value)
	{
		if (cnt == capacity) printf("Overflow\n");
		else
		{
			data[r] = value;
			r = (r + 1) % ARRMAX; // 배열 크기를 넘어가면 0으로 이동
			cnt++; // 갖고 있는 원소의 개수 카운팅
		}
	}
	void pop()
	{
		if (cnt == 0) printf("Underflow\n");
		else
		{
			data[f] = 0;
			f = (f + 1) % ARRMAX;
			cnt--;
		}
	}
	int front()
	{
		if (cnt == 0) return -1;
		else          return data[f];
	}
	int size() { return cnt; }
};

int main()
{
	Queue q;
	q.create(4);
	for (int i = 0; i < 100; i++)
	{
		q.push(i);
		q.push(i + 1);
		q.push(i + 2);
		q.push(i + 3);

		q.pop();
		q.pop();
		q.pop();
		q.pop();
	}

	q.push(1);
	q.push(2);
	printf("%d\n", q.front()); // 1

	q.pop();
	printf("%d\n", q.front()); // 2

	q.pop();

	return 0;
}