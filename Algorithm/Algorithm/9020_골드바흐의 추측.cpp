#include <stdio.h>
#include <string.h>

const int MAX = 10001;

bool prime[MAX]; // �Ҽ��� false.

int main()
{
	int t;
	scanf("%d", &t);

	// �����佺�׳׽��� ü�� �Ҽ� ���� ���ϱ�.
	prime[0] = prime[1] = true;
	for (int p = 2; p < MAX; p++)
	{
		if (prime[p]) continue;
		
		// ���� �Ҽ��� ��������, �Ҽ��� �ƴ� ��.
		for (int i = 2 * p; i < MAX; i += p)
			if(!(i % p)) prime[i] = true; // �Ҽ��� �ƴ�.
	}

	while (t--)
	{
		int num;
		scanf("%d", &num);

		int ans1, ans2, diff = MAX;
		for (int i = 2; i <= num; i++)
		{
			// ���� �Ҽ��̰� num���� i�� ���� �Ҽ����, ����.
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