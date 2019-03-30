#include <stdio.h>

int main()
{
	int n;
	scanf("%d", &n);
	
	int num = 1, cnt = 0;
	while (num < n)
	{
		num *= 3;
		cnt++;
	}
	printf("%d\n", cnt);

	return 0;
}