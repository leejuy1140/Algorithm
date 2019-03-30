#include <stdio.h>
#include <algorithm>
using namespace std;

const int MAX = 100005;

/* sort�� 3��° ���ڷ� �־��ָ�, �Ʒ� ���ؿ� ���� ����. */
bool compare(pair<int, int> &a, pair<int, int> &b)
{
	if (a.first == b.first && a.second > b.second) return false;
	else if (a.first > b.first) return false;
	else return true;
}

int main()
{
	int n;
	pair<int, int> point[MAX];

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		point[i] = make_pair(x, y);
	}

	/* x ������ ���� */
	sort(&point[0], &point[n], compare);

	/* �ִ� ���� ���ϱ� */
	double maxSlope = -1;
	for (int i = 0; i < n - 1; i++)
	{
		int dx = abs(point[i + 1].first - point[i].first);
		int dy = abs(point[i + 1].second - point[i].second);
		if (dx == 0) dx = 1; // div by 0 ����..

		double slope = (double)dy / dx;
		maxSlope = max(maxSlope, slope);
	}
	printf("%.3lf\n", maxSlope);

	return 0;
}