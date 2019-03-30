#include <stdio.h>
#include <cstdint>

const int QUOTIENT = 10007;

int n;
uint64_t m;

uint64_t power(uint64_t curM)
{
	if (curM == 1) return n;

	uint64_t answer;
	if (curM % 2)
	{
		answer = n * power(curM - 1);
		return answer % QUOTIENT;
	}
	else
	{
		answer = power(curM / 2);
		return (answer * answer) % QUOTIENT;
	}
}

int main()
{
	scanf("%d %llu", &n, &m);

	uint64_t answer;
	if (m != 1 && m % 2) answer = n * power(m - 1);
	else                 answer = power(m);
	printf("%d\n", answer % QUOTIENT);

	return 0;
}