#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;

int n, k;

// 1. 해당 인덱스에 1 또는 0을 넣는 함수
// 2. 인덱스가 n에 도달하면 1의 개수를 세고, k개면 출력
void toBin(int arr[], int idx, int cnt)
{
	if (cnt > k || idx > n) return;

	if (idx == n && k == cnt)
	{
		for (int i = 0; i < n; i++)
			printf("%d", arr[i]);
		printf("\n");
		return;
	}

	arr[idx] = 1;
	toBin(arr, idx + 1, cnt + 1);

	arr[idx] = 0;
	toBin(arr, idx + 1, cnt);
}

int main()
{
	scanf("%d %d", &n, &k);

	int num[35];
	toBin(num, 0, 0);

	return 0;
}