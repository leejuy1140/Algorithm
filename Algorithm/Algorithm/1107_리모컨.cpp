#include <stdio.h>
#include <algorithm>
using namespace std;

int n, m;
char broken[10];

int check(int num)
{
	if (!num && !broken[num]) return 1;

	int cnt = 0;
	while (num)
	{
		if (broken[num % 10]) return 0;
		num /= 10;
		cnt++;
	}
	return cnt;
}

int main()
{
	scanf("%d\n%d", &n, &m);
	for (int i = 0; i < m; i++)
	{
		int button;
		scanf("%d", &button);
		broken[button] = 1;
	}
	
	int answer = abs(100 - n);
	for (int i = n; i < 1000001; i++)
	{
		int curCnt = check(i);
		if (curCnt)
		{
			curCnt += abs(i - n);
			answer = curCnt < answer ? curCnt : answer;
			break;
		}
	}
	for (int i = n - 1; i >= 0; i--)
	{
		int curCnt = check(i);
		if (curCnt)
		{
			curCnt += abs(i - n);
			answer = curCnt < answer ? curCnt : answer;
			break;
		}
	}
	printf("%d", answer);

	return 0;
}