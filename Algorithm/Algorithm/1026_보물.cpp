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
	
	/* a�� �������ϰ� �Ǹ�, b ���� �������ϴ� �Ͱ� �ٸ� ����. */
	sort(a, a + n);
	sort(b, b + n, compare);

	int s = 0;
	for (int i = 0; i < n; i++)
		s += (a[i] * b[i]);
	printf("%d", s);
	return 0;
}