#include <stdio.h>
#include <cmath>
using namespace std;

int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
	{
		long long x, y;
		scanf("%lld %lld", &x, &y);

		// �������� �������, �׸�ŭ ���ٰ� �ٽ� ���ƿ��� ��Ģ.
		long long dist = y - x;
		long long answer = dist;
		if (dist > 3)
		{
			long long minDist = pow((long long)sqrt(dist), 2);
			long long maxDist = pow((long long)sqrt(dist) + 1, 2);
			long long midDist = (minDist + maxDist) / 2;

			long long minK = ((long long)sqrt(dist) * 2) - 1;

			if (dist == minDist) answer = minK;
			else if (dist <= midDist) answer = minK + 1;
			else answer = minK + 2;
		}
		printf("%lld\n", answer);
	}
	return 0;
}