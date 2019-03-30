#include <stdio.h>

/*
	< ��� ȣ�� >
	1. int binarySearch(int arr[], int s, int e, int v)
	   : arr�� s���� e��° �� �� v�� ã�� �Լ�
	     ã������ �ε��� ��ȯ (������ -1 ��ȯ)
	2. s > e �̸�, -1 ��ȯ
	3. �߰� ���� ����, ������ �ε��� ��ȯ.
	   v�� �� ũ�� ������ ���, ������ ���� ���

	< ����� ȣ�� >
	�߰� ���� ����, ������ �ε��� ��ȯ.
	ũ�� ���� �ε����� �߰� �� �������� ��ġ ��, �߰� �� �ٽ� ����.
	������ �� �ε����� �߰� �� �������� ��ġ ��, �߰� �� �ٽ� ����.
*/

int binarySearch(int arr[], int s, int e, int v)
{
	if (s > e) return -1;

	int mid = (s + e) / 2;

	if (v == arr[mid]) return mid;
	if (v > arr[mid]) binarySearch(arr, mid + 1, e, v);
	else			  binarySearch(arr, s, mid - 1, v);
}


int main()
{
	int n;
	scanf("%d", &n);

	int arr[100000];
	for (int i = 0; i < n; i++)
		scanf("%d", &arr[i]);

	int v;
	scanf("%d", &v);

	printf("%d\n", binarySearch(arr, 0, n - 1, v));
	
	int s = 0, e = n - 1, mid = (s + e) / 2;
	while (1)
	{
		if (s >= e)
		{
			printf("NO\n");
			break;
		}
		if (arr[mid] == v)
		{
			printf("%d\n", mid);
			break;
		}

		if (v > arr[mid]) s = mid + 1;
		else			  e = mid - 1;
		mid = (s + e) / 2;
	}

	return 0;
}