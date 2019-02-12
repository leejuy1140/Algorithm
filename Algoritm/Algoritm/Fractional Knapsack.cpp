#include <stdio.h>
#include <algorithm>
using namespace std;

const int MAX = 100005;

struct Snack { int c, w; double one; };
Snack snack[MAX];

bool compare(Snack &a, Snack &b)
{
	if (a.one > b.one) return true;
	if (a.one == b.one && a.w < b.w) return true;
	return false;
}

int main()
{
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++)
	{
		scanf("%d %d", &snack[i].w, &snack[i].c);
		snack[i].one = (double)snack[i].c / snack[i].w;
	}
	sort(&snack[0], &snack[n], compare);

	int idx = 0;
	double maxValue = 0;

	while (m)
	{
		if (idx >= n) break;

		int weight = snack[idx].w;
		if (weight > m) weight = m;

		double value = snack[idx].one * weight;
		maxValue += value;
		m -= weight;
		idx++;
	}
	printf("%.3lf\n", maxValue);

	return 0;
}