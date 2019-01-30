#include <stdio.h>
#include <algorithm>
using namespace std;
int main()
{
	/*
		정답이 b라면,
		b의 fx 값은 a보다 작고, (b+1)의 fx 값은 a보다 큼.
	*/

	uint64_t a;
	scanf("%llu", &a);

	uint64_t pre = 0; // f(x) 결과가 a보다 작으면 1로 설정
	uint64_t max = sqrt(a) + 1;
	uint64_t mid = max / 2;
	while (1)
	{
		if (max < mid) break;

		uint64_t res = mid * mid + mid;

		// a와 같으면 해당 수가 정답
		if (res == a)
		{
			printf("%d", mid);
			break;
		}

		// a보다 작으면 커지는 수가 나올 때까지 새로운 중간 값 계산
		if (res < a)
		{
			pre = mid;
			mid += (max - mid) / 2;

			// 새로운 중간 값이 이전 값과 동일하다면, 이전 값이 정답
			if (pre == mid)
			{
				printf("%d", pre);
				break;
			}
		}
		else
		{
			// a보다 작은 수 결과가 나올 때까지 계속 절반씩 줄여나감
			if (!pre)
			{
				max = mid;
				mid /= 2;
			}

			// 이전에 a보다 작았는데, 이번에 a보다 크면 작은 수가 정답
			else
			{
				printf("%d", pre);
				break;
			}
		}
	}

	return 0;
}