#include <stdio.h>
#include <cmath>

int main()
{
	int n;
	scanf("%d", &n);

	int num = n, curLen = 0;
	while (num) { num /= 10; curLen++; }
	
	unsigned long long newLen = 0;
	for (int i = 1; i <= curLen; i++)
	{
		if (i == curLen) newLen += (abs(pow(10, i - 1) - n) + 1) * i;
		else			 newLen += pow(10, i - 1) * 9 * i;
	}
	printf("%llu", newLen);

	return 0;
}