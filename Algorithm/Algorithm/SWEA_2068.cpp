#include <stdio.h>

int main()
{
	int t;
	scanf("%d", &t);
	for (int tt = 1; tt <= t; tt++)
	{
		int maxNum = 0;
		for (int i = 0; i < 10; i++)
		{
			int num;
			scanf("%d", &num);
			if (num > maxNum) maxNum = num;
		}
		printf("#%d %d\n", tt, maxNum);
	}
	return 0;
}