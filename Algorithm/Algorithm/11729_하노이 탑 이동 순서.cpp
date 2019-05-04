#include <iostream>
#include <cmath>
using namespace std;

/* num개의 원판을 from에서 by를 경유하여 to로 이동. */
void Hanoi(int num, int from, int by, int to)
{
	if (!num) return;
	Hanoi(num - 1, from, to, by); // 1. 맨 아래 원판 제외한 num-1개의 원판을 by로 이동.
	printf("%d %d\n", from, to);  // 2. 맨 아래 원판을 to로 이동.
	Hanoi(num - 1, by, from, to); // 3. by로 이동시킨 num-1개의 원판을 다시 to로 이동.
}

int main(void)
{
	int n;
	scanf("%d", &n);

	// 하노이탑 총 이동 횟수는 2^n - 1
	int cnt = pow(2, n) - 1;
	printf("%d\n", cnt);
	Hanoi(n, 1, 2, 3);

	return 0;
}