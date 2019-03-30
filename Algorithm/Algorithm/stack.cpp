#include <stdio.h>
#include <stdlib.h>

struct Stack
{
	int *stack;
	int top = -1;
	int capacity;

	void create(int size)
	{
		stack = (int *)malloc(sizeof(int) * size);
		capacity = size;
	}
	void push(int data)
	{
		if (top >= capacity - 1)
			printf("Stack overflow\n");
		else stack[++top] = data;
	}
	void pop()
	{
		if (top == -1)
			printf("Stack underflow\n");
		else top--;
	}
	int getTop()
	{
		if (top <= -1) return -1;
		return stack[top];
	}
	int size() { return top; }
};

int main()
{
	Stack s;
	s.create(5);

	s.push(5);
	s.push(8);
	s.push(10);
	s.push(6);
	s.push(1);
	s.push(3);
	printf("top: %d\n", s.getTop());
	printf("size: %d\n", s.size());

	s.pop();
	s.pop();
	s.pop();
	s.pop();
	printf("top: %d\n", s.getTop());
	printf("size: %d\n", s.size());

	s.pop();
	s.pop();

	return 0;
}