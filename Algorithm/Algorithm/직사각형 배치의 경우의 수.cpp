#include <stdio.h>

const int MAX = 101;
const int QUOTIENT = 1000007;

int main()
{
	int n, fibo[MAX];
	scanf("%d", &n);

/*
	2*4의 직사각형을 채우는 경우의 수라면,
	마지막 칸에 1*2 블럭 하나를 넣을 지, 2*1 블럭 두개를 넣을지로 나눌 수 있음.
	따라서, 마지막 칸을 채우고 남은 칸인 2*3과 2*2를 채우는 경우의 수를 합한 것이 정답. 
	이는 피보나치 수열과 같음.
*/

	fibo[0] = fibo[1] = 1;
	for (int i = 2; i <= n; i++)
	{
		fibo[i] = fibo[i - 1] + fibo[i - 2];
		if (fibo[i] > QUOTIENT) fibo[i] %= QUOTIENT;
	}
	printf("%d", fibo[n]);

	return 0;
}