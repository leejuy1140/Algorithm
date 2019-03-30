#include <stdio.h>

int main()
{
	int n; scanf("%d", &n);

	// 구슬의 개수가 4개가 되면, 철수가 어떻게 가져가도 짐.
	if (n % 4) printf("YES");
	else       printf("NO");
	
	return 0;
}