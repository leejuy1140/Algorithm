#include <stdio.h>
#include <stack>
using namespace std;

int main()
{
	int n;
	scanf("%d", &n);

	stack<pair<int, int>> receiver;
	for (int i = 1; i <= n; i++)
	{
		int sender;
		scanf("%d", &sender);

		while (!receiver.empty())
		{
			if (receiver.top().first > sender) break;
			receiver.pop();
		}

		if (receiver.empty()) printf("0 ");
		else printf("%d ", receiver.top().second);

		receiver.push(pair<int, int>(sender, i));
	}

	return 0;
}