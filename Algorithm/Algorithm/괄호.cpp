#include <stdio.h>
#include <string.h>

struct Stack
{
	char data[55];
	int top = -1;

	void push(char x)
	{
		if (top >= 55) return;
		data[++top] = x;
	}
	void pop()
	{
		if (top == -1) return;
		top--;
	}
	char getTop()
	{
		if (top == -1) return -1;
		return data[top];
	}
};

int main()
{
	char bracket[55];
	scanf("%s", bracket);

	Stack all, close;

	for (int i = 0; i < strlen(bracket); i++)
		all.push(bracket[i]);

	int flag = 0;
	while (1)
	{
		if (all.getTop() == -1)
		{
			if (close.getTop() != -1) flag = 1;
			break;
		}

		char allTop = all.getTop();
		char closeTop = close.getTop();
		all.pop();

		// ºñ±³ ½ºÅÃÀÌ ºñ¾ú´Âµ¥, ¿­¸° °ýÈ£¸é NO
		if (closeTop == -1 && allTop != ')')
		{
			flag = 1;
			break;
		}

		// ´ÝÈù °°Àº °ýÈ£¸é, push
		if (allTop == ')') close.push(allTop);
		else			   close.pop();
	}

	if (flag) printf("NO");
	else	  printf("YES");

	return 0;
}