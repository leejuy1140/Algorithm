#include <stdio.h>
#include <string.h>
#include <stack>
using namespace std;

int main()
{
	char bracket[35];
	scanf("%s", bracket);

	if (strlen(bracket) % 2 || bracket[0] == ')' || bracket[0] == ']')
	{ printf("0"); return 0; }

	stack<int> s;
	s.push(bracket[0]);

	for (int i = 1; i < strlen(bracket); i++)
	{
		// ���� ��ȣ�� ���ÿ� push
		if (bracket[i] == '[' || bracket[i] == '(')
			s.push(bracket[i]);

		// ���� ��ȣ�ų� ������ ��� ó��
		else
		{
			if (s.empty()) { printf("0"); return 0; }
			int top = s.top();
			s.pop();

			int sum = 0; // ������ ���, �� ����
			while (top != '[' && top != '(')
			{
				sum += top;

				if (s.empty()) { printf("0"); return 0; }
				top = s.top();
				s.pop();
			}

			if (top == '[' && bracket[i] == ']')
			{
				if (sum) sum *= 3;
				else	 sum += 3;
				s.push(sum);
			}
			else if (top == '(' && bracket[i] == ')')
			{
				if (sum) sum *= 2;
				else	 sum += 2;
				s.push(sum);
			}
			else { printf("0"); return 0; }
		}
	}

	int answer = 0;
	while (!s.empty())
	{
		answer += s.top();
		s.pop();
	}
	printf("%d", answer);

	return 0;
}