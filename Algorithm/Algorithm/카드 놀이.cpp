#include <stdio.h>
#include <algorithm>
using namespace std;

const int MAX = 100000;

int main()
{
	int n, card[MAX], sum[MAX];
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &card[i]);	
/* 
	sum[i] = max(sum[i-1], sum[i-2] + card[i], sum[i-3] + card[i-1] + card[i]) 
*/
	sum[0] = card[0];
	sum[1] = card[0] + card[1];
	sum[2] = max(card[0] + card[2], sum[1]);
	sum[2] = max(sum[2], card[1] + card[2]);

	for (int i = 3; i < n; i++)
	{
		sum[i] = max(sum[i - 1], sum[i - 2] + card[i]);
		sum[i] = max(sum[i], sum[i - 3] + card[i - 1] + card[i]);
	}
	printf("%d", sum[n - 1]);

	return 0;
}