#include <stdio.h>

/*  
	< ��� 1 >
	1. quickSort(arr[], s, e): arr�� s���� e���� �������ϴ� �Լ�
	2. s >= e: ���� (s�� e���� ũ�ٸ� ���ڰ� ���� ���)
	3. pivot���� �۰ų� ����, ū ���� �з��� ��, ������ �� ����.
	int left[], right[];
	getLeft(arr, s+1, e, pivot, left);
	getLeft(arr, s+1, e, pivot, right);
	arr <- left + [pivot] + right;
	quickSort(arr, s, s + left_cnt - 1);
	quickSort(arr, s + left_cnt + 1, e);
*/

// arr�� s���� e���� ���ڵ� �߿��� pivot���� �۰ų� ���� ���� result�� ä��� �Լ�
int getLeft(int arr[], int s, int e, int pivot, int result[])
{
	int idx = 0;
	for (int i = s; i <= e; i++)
	{
		if (arr[i] <= pivot)
			result[idx++] = arr[i];
	}
	return idx;
}

// arr�� s���� e���� ���ڵ� �߿��� pivot���� ū ���� result�� ä��� �Լ�
int getRight(int arr[], int s, int e, int pivot, int result[])
{
	int idx = 0;
	for (int i = s; i <= e; i++)
	{
		if (arr[i] > pivot)
			result[idx++] = arr[i];
	}
	return idx;
}

void quickSort(int arr[], int s, int e)
{
	if (s >= e) return;

	int pivot = arr[s]; // �� ó�� ���� pivot���� ����.
	
	// pivot���� �۰ų� ���� ��, ũ�ų� ���� ���� �迭�� ����
	int left[100000], right[100000];
	int left_cnt = getLeft(arr, s + 1, e, pivot, left);
	int right_cnt = getRight(arr, s + 1, e, pivot, right);

	// 4 8 2 2 1 7 6 2 3 1
	// pivot: 4
	// left: 2 2 1 2 3 1
	// right: 8 7 6
	// arr -> 2 2 1 2 3 1 [4] 8 7 6

	for (int i = 0; i < left_cnt; i++)
		arr[s + i] = left[i];
	arr[s + left_cnt] = pivot;
	for (int i = 0; i < right_cnt; i++)
		arr[s + left_cnt + 1 + i] = right[i];

	quickSort(arr, s, s + left_cnt - 1);
	quickSort(arr, s + left_cnt + 1, e);
}


int main()
{
	int n;
	int numbers[100000];
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &numbers[i]);

	quickSort(numbers, 0, n - 1);
	for (int i = 0; i < n; i++)
		printf("%d ", numbers[i]);

	return 0;
}