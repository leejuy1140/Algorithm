#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
using namespace std;

int n;
long long k;

void binary(int s, int e)
{
	if (s > e) return;

	int mid = (s + e) / 2;
	int same = 0;
	long long idx = 0;

	for (int dan = 1; dan <= n; dan++)
	{
		if (mid / dan > n) idx += n;
		else
		{
			if (!(mid % dan)) same++;
			idx += mid / dan;
		}
	}

	if (idx - same + 1 <= k && idx >= k)
	{
		printf("%d\n", mid);
		return;
	}

	if (idx >= k) binary(s, mid - 1);
	else         binary(mid + 1, e);
}

int main()
{
	scanf("%d %lld", &n, &k);
	int maximum = n * n;
	binary(1, maximum);
	return 0;
}