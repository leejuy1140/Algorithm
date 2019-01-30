#include <stdio.h>
#include <vector>
#include <stdint.h>
using namespace std;

uint64_t n, m, answer;
vector<uint64_t> tree;

void binarySearch(uint64_t s, uint64_t e)
{
	if (s > e) return;

	uint64_t mid = (s + e) / 2;

	uint64_t sum = 0;
	for (int i = 0; i < n; i++)
	{
		if (mid < tree[i])
			sum += tree[i] - mid;
	}

	if (sum >= m)
	{
		answer = mid;
		binarySearch(mid + 1, e);
	}
	else binarySearch(s, mid - 1);
}

int main()
{
	scanf("%d %d", &n, &m);

	tree.resize(n);

	uint64_t maximum = 0;
	for (int i = 0; i < n; i++)
	{
		scanf("%llu", &tree[i]);
		if (tree[i] > maximum)
			maximum = tree[i];
	}

	binarySearch(0, maximum);
	printf("%llu\n", answer);

	return 0;
}