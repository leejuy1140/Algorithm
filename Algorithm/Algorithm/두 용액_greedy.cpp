#include <stdio.h>
#include <algorithm>
using namespace std;

const int MAX = 100005;

bool compare(int a, int b)
{
	if (abs(a) > abs(b)) return false;
	else				 return true;
}

int main()
{
	int n, data[MAX];
	bool acid = 0, alkaline = 0;
	
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &data[i]);
		if (data[i] < 0 && !acid)	  acid = 1;
		if (data[i] > 0 && !alkaline) alkaline = 1;
	}

	sort(&data[0], &data[n], compare);

	// 산성만 있거나, 알칼리성만 있는 경우
	if (acid && !alkaline)
	{
		printf("%d %d\n", data[1], data[0]);
		return 0;
	}
	if (!acid && alkaline)
	{
		printf("%d %d\n", data[0], data[1]);
		return 0;
	}

	// 둘 다 있는 경우
	int minIdx = -1, minValue = 999999999;
	for (int i = 0; i < n - 1; i++)
	{
		int value = abs(data[i] + data[i + 1]);
		
		if (value == minValue)
		{
			int curMin = min(data[i], data[i + 1]);
			int prevMin = min(data[minIdx], data[minIdx + 1]);
			if (curMin < prevMin) minIdx = i;
		}
		else if (value < minValue)
		{
			minIdx = i;
			minValue = value;
		}
	}
	
	if (data[minIdx] > data[minIdx + 1])
		printf("%d %d\n", data[minIdx + 1], data[minIdx]);
	else printf("%d %d\n", data[minIdx], data[minIdx + 1]);

	return 0;
}