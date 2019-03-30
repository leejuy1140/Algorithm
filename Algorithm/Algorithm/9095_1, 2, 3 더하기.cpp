#include <stdio.h>

int element[3] = { 1, 2, 3 };

int solution(int n)
{
	if (n < 0) return 0;
	if (n == 0) return 1;

	int ret = 0;
	for (int i = 0; i < 3; i++)
		ret += solution(n - element[i]);
	return ret;
}

int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
	{
		int num;
		scanf("%d", &num);
		printf("%d\n", solution(num));
	}
	return 0;
}