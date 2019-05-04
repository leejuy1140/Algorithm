#include <iostream>
#include <cmath>
using namespace std;

/* num���� ������ from���� by�� �����Ͽ� to�� �̵�. */
void Hanoi(int num, int from, int by, int to)
{
	if (!num) return;
	Hanoi(num - 1, from, to, by); // 1. �� �Ʒ� ���� ������ num-1���� ������ by�� �̵�.
	printf("%d %d\n", from, to);  // 2. �� �Ʒ� ������ to�� �̵�.
	Hanoi(num - 1, by, from, to); // 3. by�� �̵���Ų num-1���� ������ �ٽ� to�� �̵�.
}

int main(void)
{
	int n;
	scanf("%d", &n);

	// �ϳ���ž �� �̵� Ƚ���� 2^n - 1
	int cnt = pow(2, n) - 1;
	printf("%d\n", cnt);
	Hanoi(n, 1, 2, 3);

	return 0;
}