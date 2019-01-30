#include <stdio.h>
#include <string.h>
#include <vector>
#define CAPACITY 27
using namespace std;

struct Stack
{
	int data[27];
	int top = -1;

	void push(int x)
	{
		if (top >= CAPACITY - 1) return;
		data[++top] = x;
	}
	void pop()
	{
		if (top == -1) return;
		top--;
	}
	int getTop()
	{
		if (top == -1) return -1;
		else return data[top];
	}
};

int main()
{
	char alpha[CAPACITY + 1];
	scanf("%s", alpha);

	Stack dish;
	vector<int> path; // 1: push, 2: pop

	bool chk[CAPACITY];
	memset(chk, 0, CAPACITY);

	for (int i = 0; i < strlen(alpha); i++)
	{
		int toNum = alpha[i] - 'a';

		if (!chk[toNum]) // 스택에 없으면
		{
			for (int j = 0; j <= toNum; j++)
			{
				if (chk[j]) continue;
				dish.push(j);
				path.push_back(1);
				chk[j] = 1;
			}
		}

		int topNum = dish.getTop();
		if (topNum == toNum)
		{
			dish.pop();
			path.push_back(2);
		}
		else
		{
			printf("impossible\n");
			return 0;
		}
	}

	for (int i = 0; i < path.size(); i++)
	{
		if (path[i] == 1) printf("push\n");
		if (path[i] == 2) printf("pop\n");
	}

	return 0;
}