#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;

int n, k;

// 1. �ش� �ε����� 1 �Ǵ� 0�� �ִ� �Լ�
// 2. �ε����� n�� �����ϸ� 1�� ������ ����, k���� ���
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