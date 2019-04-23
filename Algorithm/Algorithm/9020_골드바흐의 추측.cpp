#include <stdio.h>
#include <string.h>

const int MAX = 10001;

bool prime[MAX]; // 소수면 false.

int main()
{
	int t;
	scanf("%d", &t);

	// 에라토스테네스의 체로 소수 먼저 구하기.
	prime[0] = prime[1] = true;
	for (int p = 2; p < MAX; p++)
	{
		if (prime[p]) continue;
		
		// 현재 소수로 나눠지면, 소수가 아닌 것.
		for (int i = 2 * p; i < MAX; i += p)
			if(!(i % p)) prime[i] = true; // 소수가 아님.
	}

	while (t--)
	{
		int num;
		scanf("%d", &num);

		int ans1, ans2, diff = MAX;
		for (int i = 2; i <= num; i++)
		{
			// 만약 소수이고 num에서 i뺀 값도 소수라면, 저장.
			if (!prime[i] && !prime[num - i])
			{
				int curDiff = i - (num - i);
				if (curDiff < 0) curDiff *= -1;

				if (curDiff < diff)
				{
					diff = curDiff;
					if (i < num - i)
					{
						ans1 = i;
						ans2 = num - i;
					}
					else
					{
						ans1 = num - i;
						ans2 = i;
					}
				}
			}
		}
		printf("%d %d\n", ans1, ans2);
	}


	return 0;
}