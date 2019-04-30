#include <stdio.h>

int main()
{
	char str[205];
	scanf("%s", str);
	
	int idx = 0;
	while (str[idx] != '\0')
	{
		printf("%d ", str[idx] - 'A' + 1);
		idx++;
	}
	return 0;
}