#include <stdio.h>

/*
	1. mergerSort(int arr[], int s, int e)
	   arr�� s��° ������ e��° ������ �պ� �����ϴ� �Լ�
	2. s >= e �� ���, ����
	3. ���� ����, ������ �������� ���� ��, ��ġ��
		mid = (s+e) / 2;
		mergeSort(arr, s, mid);
		mergeSort(arr, mid + 1, e);
		merging(s, mid, mid + 1, e);

	+ merging(s, mid, mid + 1, e):
	  ���� ���ݰ� ������ ������ ���� ���ĵ� �迭�� ����� �Լ�
*/

// ���� ���ݰ� ������ ������ ���� ���ĵ� �迭�� ����� �Լ�
void merging(int arr[], int s1, int e1, int s2, int e2)
{
	int p = s1; // ���� ������ �ּҰ�
	int q = s2; // ������ ������ �ּҰ�

	// arr�� ���ĵ� ����� ������Ʈ�ϸ� ���� ������� ����
	// tmp �迭�� ������ ��, arr�� ���ĵ� ��� ����
	int tmp[100];
	int idx = 0;

	while (1)
	{
		if (p > e1 || q > e2) break;

		if (arr[p] < arr[q]) tmp[idx++] = arr[p++];
		else				 tmp[idx++] = arr[q++];
	}

	if (p > e1)
	{
		for (int i = q; i <= e2; i++)
			tmp[idx++] = arr[i];
	}
	if (q > e2)
	{
		for (int i = p; i <= e1; i++)
			tmp[idx++] = arr[i];
	}

	// s1 ~ e2���� tmp�� ���� ����
	// tmp�迭�� 0������ �����ؼ� �־��� ������ i���� s1��ŭ�� ��
	for (int i = s1; i <= e2; i++)
		arr[i] = tmp[i - s1];
}

void mergeSort(int arr[], int s, int e)
{
	if (s >= e) return;
	
	// 1������ �� ������, ��� �������� ����
	int mid = (s + e) / 2;
	mergeSort(arr, s, mid);
	mergeSort(arr, mid + 1, e);
	
	// arr[s ~ mid], arr[mid+1 ~ e]�� ������ �� ����
	// ó�� merging �� ����, 2������ �� !
	merging(arr, s, mid, mid + 1, e);
}
int main()
{
	int n;
	int numbers[100];
	scanf("%d", &n);
	for(int i = 0; i < n; i++)
		scanf("%d", &numbers[i]);

	mergeSort(numbers, 0, n - 1);

	for (int i = 0; i < n; i++)
		printf("%d ", numbers[i]);

	return 0;
}