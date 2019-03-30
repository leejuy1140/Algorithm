#include <stdio.h>
using namespace std;

int n, r;
char arr[27];
bool check[26];

void makePermutation(int idx)
{
	if (idx == r)
	{
		for (int i = 0; i < r; i++)
			printf("%c", arr[i] + 'a');
		printf("\n");
		return;
	}

	for (int next = 0; next < n; next++)
	{
		if (check[next]) continue;

		arr[idx] = next;
		check[next] = 1;
		makePermutation(idx + 1);
		check[next] = 0;
	}
}

int main()
{
	scanf("%d %d", &n, &r);
	makePermutation(0);
	return 0;
}