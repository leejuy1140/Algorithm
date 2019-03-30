#include <stdio.h>
#include <vector>
using namespace std;

int main()
{
	int n;
	scanf("%d", &n);
	vector<int> tree(n + 1);

	int x, y;
	scanf("%d %d", &x, &y);

	for (int i = 0; i < n - 1; i++)
	{
		int a, b;
		scanf("%d %d", &a, &b);
		tree[b] = a; // b의 부모는 a
	}

	int xx = x, yy = y;
	while (1)
	{
		if (xx == yy)
		{
			printf("%d\n", xx);
			break;
		}

		if (yy) yy = tree[yy];
		else
		{
			xx = tree[xx];
			yy = y;
		}
	}

	return 0;
}