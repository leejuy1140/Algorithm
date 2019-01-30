#include <stdio.h>

/* 0 2 3 4 5
	 f      r */
struct Queue
{
	int data[10];
	int f; // 맨 앞 데이터를 가리킴
	int r; // 다음에 데이터가 들어올 곳을 가리킴
	int capacity;

	void create(int size)
	{
		capacity = size;
		f = 0; r = 0;
	}
	void push(int value)
	{
		// 내가 가지고 있는 원소의 개수가 용량보다 큼
		if (r - f >= capacity) printf("Overflow\n");
		else				   data[r++] = value;
	}
	void pop()
	{
		if (r - f <= 0) printf("Underflow\n");
		else		    { data[f] = 0; f++; }
	}
	int front()
	{
		if (r - f <= 0) return -1;
		else			return data[f];
	}
	int size() { return r - f; }
};

int main()
{
	Queue q;
	q.create(5);

	q.push(5);
	q.push(3);
	q.push(8);
	q.push(1);
	q.push(9);
	q.push(7); // Overflow
	printf("%d\n", q.front()); // 5

	q.pop();
	printf("%d\n", q.front()); // 3
	q.pop();
	q.pop();
	q.pop();
	q.pop();
	q.pop(); // Underflow

	return 0;
}