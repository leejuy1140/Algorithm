#include <stdio.h>
#include <algorithm>
using namespace std;

int main() {

	//Please Enter Your Code Here
	int n, m;
	scanf("%d %d", &n, &m);


	int num, flag = 0;

	int up2 = 0, up5 = 0;
	for (int i = n; i > max(m, n - m);)
	{
		if (!flag)
		{
			num = i;
			flag = 1;
		}
		if (num % 5 != 0 && num % 2 != 0)
		{
			i--;
			flag = 0;
		}

		if (num % 5 == 0)
		{
			up5++;
			num /= 5;
		}
		if (num % 2 == 0)
		{
			up2++;
			num /= 2;
		}
	}
	//printf("분자 2: %d, 5: %d\n", up2, up5);

	flag = 0;
	int down2 = 0, down5 = 0;
	for (int i = min(m, n - m); i > 0;)
	{
		if (!flag)
		{
			num = i;
			flag = 1;
		}
		if (num % 5 != 0 && num % 2 != 0)
		{
			i--;
			flag = 0;
		}

		if (num % 5 == 0)
		{
			down5++;
			num /= 5;
		}
		if (num % 2 == 0)
		{
			down2++;
			num /= 2;
		}
	}
	//printf("분모 2: %d, 5: %d\n", down2, down5);

	int two = up2 - down2;
	int five = up5 - down5;
	printf("%d", min(two, five));

	return 0;
}