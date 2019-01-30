#include <stdio.h>

/*  
	< 방법 1 >
	1. quickSort(arr[], s, e): arr의 s부터 e까지 퀵정렬하는 함수
	2. s >= e: 종료 (s가 e보다 크다면 숫자가 없는 경우)
	3. pivot보다 작거나 같고, 큰 값을 분류한 후, 각각을 퀵 정렬.
	int left[], right[];
	getLeft(arr, s+1, e, pivot, left);
	getLeft(arr, s+1, e, pivot, right);
	arr <- left + [pivot] + right;
	quickSort(arr, s, s + left_cnt - 1);
	quickSort(arr, s + left_cnt + 1, e);
*/

// arr의 s부터 e까지 숫자들 중에서 pivot보다 작거나 같은 값을 result에 채우는 함수
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

// arr의 s부터 e까지 숫자들 중에서 pivot보다 큰 값을 result에 채우는 함수
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

	int pivot = arr[s]; // 맨 처음 값을 pivot으로 정함.
	
	// pivot보다 작거나 같은 값, 크거나 같은 값을 배열에 저장
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