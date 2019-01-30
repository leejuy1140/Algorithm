#include <stdio.h>

/*
	< 재귀 호출 >
	1. int binarySearch(int arr[], int s, int e, int v)
	   : arr의 s부터 e번째 값 중 v를 찾는 함수
	     찾았으면 인덱스 반환 (없으면 -1 반환)
	2. s > e 이면, -1 반환
	3. 중간 값과 비교해, 같으면 인덱스 반환.
	   v가 더 크면 오른쪽 재귀, 작으면 왼쪽 재귀

	< 비재귀 호출 >
	중간 값과 비교해, 같으면 인덱스 반환.
	크면 시작 인덱스를 중간 값 다음으로 위치 후, 중간 값 다시 구함.
	작으면 끝 인덱스를 중간 값 이전으로 위치 후, 중간 값 다시 구함.
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