 #include <stdio.h>
#include <string.h>
using namespace std;

// 1 ~ 123456*2
#define SIZE 123456*2+1

int main() {

	//Please Enter Your Code Here

	bool check[SIZE]; // 1: 소수 X
	memset(check, 0, SIZE);

	// 에라토스테네스의 체 거르기
	// x 2 3 x 5 x 7 x x x 11 x 13 x x x
	check[0] = check[1] = 1;
	for (int num = 2; num < SIZE; num++)
	{
		if (check[num]) continue;

		for (int i = num * 2; i < SIZE; i += num)
		{
			if (!check[i] && i % num == 0)
				check[i] = 1;
		}
	}


	while (1)
	{
		int n;
		scanf("%d", &n);

		if (n == 0) break;

		int cnt = 0;
		for (int num = n + 1; num <= 2 * n; num++)
		{
			if (check[num]) continue;
			else           cnt++;
		}
		printf("%d\n", cnt);
	}

	return 0;
}