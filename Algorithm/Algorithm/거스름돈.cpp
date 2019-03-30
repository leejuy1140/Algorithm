#include <stdio.h>

int main()
{
	int n, idx = 0, answer = 0;
	int coin[5] = { 500, 100, 50, 5, 1 };
	scanf("%d", &n);

	while (n > 0)
	{
		if (coin[idx] > n)
		{ idx++; continue; }

		answer++;
		n -= coin[idx];
	}
	printf("%d\n", answer);
	
	return 0;
}