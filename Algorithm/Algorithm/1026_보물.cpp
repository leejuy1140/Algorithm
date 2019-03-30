#include <stdio.h>
#include <algorithm>
using namespace std;

const int MAX = 51;
int n, a[MAX], b[MAX];

bool compare(int i, int j)
{ return i > j; }

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d", &a[i]);
	for (int i = 0; i < n; i++) scanf("%d", &b[i]);
	
	/* a를 재정렬하게 되면, b 또한 재정렬하는 것과 다름 없음. */
	sort(a, a + n);
	sort(b, b + n, compare);

	int s = 0;
	for (int i = 0; i < n; i++)
		s += (a[i] * b[i]);
	printf("%d", s);
	return 0;
}