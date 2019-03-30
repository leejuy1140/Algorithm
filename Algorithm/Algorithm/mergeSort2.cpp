#include <stdio.h>
#include <vector>
using namespace std;

void merging(int arr[], int s1, int e1, int s2, int e2)
{
	int p = s1;
	int q = s2;
	vector<int> tmp;

	while (p <= e1 && q <= e2)
	{
		if (arr[p] < arr[q]) tmp.push_back(arr[p++]);
		else				 tmp.push_back(arr[q++]);
	}

	if (p > e1)
	{
		for (int i = q; i <= e2; i++)
			tmp.push_back(arr[i]);
	}
	if (q > e2)
	{
		for (int i = p; i <= e1; i++)
			tmp.push_back(arr[i]);
	}

	for (int i = s1; i <= e2; i++)
		arr[i] = tmp[i - s1];
}

void mergeSort(int arr[], int s, int e)
{
	if (s >= e) return;

	int mid = (s + e) / 2;
	mergeSort(arr, s, mid);
	mergeSort(arr, mid + 1, e);
	
	merging(arr, s, mid, mid + 1, e);
}

int main()
{
	int n;
	scanf("%d", &n);

	int numbers[100000];
	for (int i = 0; i < n; i++)
		scanf("%d", &numbers[i]);

	/*
	 1. mergeSort(arr, s, e): arr을 s부터 e까지 합병정렬.
	 2. s >= e 이면, 1 조각이므로 종료.
	 3. 왼쪽 절반, 오른쪽 절반으로 나눈 후, 합치기
	 mid = (s+e)/2
	 mergeSort(arr, s, mid);
	 mergeSort(arr, mid+1, e);
	 merging(arr, s, mid, mid+1, e);
	*/

	mergeSort(numbers, 0, n - 1);
	for (int i = 0; i < n; i++)
		printf("%d ", numbers[i]);

	return 0;
}