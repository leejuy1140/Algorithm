#include <stdio.h>

int main() {

	//Please Enter Your Code Here
	int n;
	scanf("%d", &n);

	int flag = 1;
	for (int prime = 2; n > 1;)
	{
		if (n % prime == 0)
		{
			printf("%d\n", prime);
			n /= prime;
		}
		else
		{
			prime++;
		}
	}

	return 0;
}