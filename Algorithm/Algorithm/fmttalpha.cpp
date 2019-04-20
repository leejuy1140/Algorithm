#include <stdio.h>
#include <cmath>
using namespace std;

/*
	이동할 수 있는 최대거리
	광년 - 경로 - k
	2 - 11 - k
	4 - 121 - 3
	9 - 12321 - 5     -- min
	11 - 123321 - 6
	(12 - 123321 - 6) -- mid
	13 - 1232221 - 7
	16 - 1234321 - 7  -- max
	25 - 123454321 - 9
	36 - 12345654321
*/

int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
	{
		int a, b;
		scanf("%d %d", &a, &b);

		int distance = b - a;
		if (distance <= 3)
		{
			printf("%d", distance);
			continue;
		}

		int min = sqrt(distance); min = pow(min, 2);
		int max = pow(ceil(sqrt(distance)), 2);
		int mid = max - sqrt(max);

		int min_k = 2 * sqrt(min) - 1;
		int max_k = 2 * sqrt(max) - 1;
		int mid_k = min_k + 1;

		if (distance == min)
			printf("%d", min_k);
		else if (distance <= mid)
			printf("%d", mid_k);
		else
			printf("%d", max_k);
	}
	return 0;
}