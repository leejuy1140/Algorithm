#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

bool chkUpper(char a) {
	return (a >= 'A' && a <= 'Z');
}

bool chkLower(char a) {
	return (a >= 'a' && a <= 'z');
}

bool chkNum(char a) {
	return (a >= '0' && a <= '9');
}

int main(void)
{
	char input[1000];
	scanf("%s", input);

	queue<char> alpha, number;
	for (int i = 0; i < strlen(input); i++)
	{
		if (!chkNum(input[i])) alpha.push(input[i]);
		else				   number.push(input[i]);
	}

	// 맞추기
	vector<char> answer;
	while (!alpha.empty() && !number.empty())
	{
		char upper = alpha.front();
		char num = number.front();
		alpha.pop();
		number.pop();
		if (!chkUpper(upper)) break;
		
		answer.push_back(upper);
		if (!alpha.empty())
		{
			if (chkLower(alpha.front()))
			{
				answer.push_back(alpha.front());
				alpha.pop();
			}
		}
		
		if (num == '1') // 1과 10처리.
		{
			if (!number.empty())
			{
				if (number.front() == '0')
				{
					answer.push_back('1');
					answer.push_back('0');
					number.pop();
				}
			}
		}
		else answer.push_back(num);
	}

	if (!alpha.empty() || !number.empty()) printf("error");
	else
	{
		for (int i = 0; i < answer.size(); i++)
			printf("%c", answer[i]);
	}
	return 0;
}