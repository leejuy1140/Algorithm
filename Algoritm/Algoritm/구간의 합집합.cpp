#include <stdio.h>

int n;
long long which;
int section[20000];

void binary(int s, int e)
{
	if (s > e) return;

	int mid = (s + e) / 2;
	int same = 0;
	long long idx = -1;

	for (int i = 0; i < 2 * n; i += 2)
	{
		if (section[i + 1] < mid)
			idx += section[i + 1] - section[i] + 1;
		else if (section[i] <= mid)
		{
			idx += mid - section[i] + 1;
			same++;
		}
	}

	if (which >= idx - same + 1 && which <= idx)
	{
		printf("%d\n", mid);
		return;
	}

	if (idx >= which) binary(s, mid - 1);
	else              binary(mid + 1, e);
}

int main()
{
	scanf("%d", &n);
	int maxNum = 0;
	for (int i = 0; i < 2 * n; i++)
	{
		scanf("%d", &section[i]);
		if (maxNum < section[i]) maxNum = section[i];
	}
	scanf("%lld", &which);

	binary(1, maxNum);

	return 0;
}