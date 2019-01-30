#include <stdio.h>
#include <algorithm>
using namespace std;

/*
	< 방법 2 >
	1. quickSort(int arr[], int pivot, int left, int right):
		pivot의 위치를 퀵 정렬로 정하는 함수
	2. left >= right 종료
	3. 구현
		while(1)
		{
			while(arr[l] <= arr[pivot]) l++;
			while(arr[r] > arr[pivot])  r--;
			if(l >= r) break;
			swap(arr[l], arr[r]);
		}
		swap(arr[pivot], arr[r]);
		quickSort(arr, pivot, pivot, r - 1);
		quickSort(arr, r + 1, r + 1, right);
	*/

void quickSort(int arr[], int pivot, int left, int right)
{
	if (left >= right) return;

	int l = left;
	int r = right;

	while (1)
	{
		while (arr[pivot] >= arr[l]) l++;
		while (arr[pivot] < arr[r])  r--;

		if (l >= r) break;

		swap(arr[l], arr[r]);
	}

	swap(arr[pivot], arr[r]);

	// r 이 pivot 값의 인덱스가 됨 !
	quickSort(arr, pivot, pivot, r - 1);
	quickSort(arr, r + 1, r + 1, right);
}

int main()
{
	int n;
	int numbers[100000];
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &numbers[i]);

	quickSort(numbers, 0, 0, n - 1);
	for (int i = 0; i < n; i++)
		printf("%d ", numbers[i]);

	return 0;
}