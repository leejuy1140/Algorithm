#include <stdio.h>

/*
	1. mergerSort(int arr[], int s, int e)
	   arr을 s번째 값부터 e번째 값까지 합병 정렬하는 함수
	2. s >= e 인 경우, 종료
	3. 왼쪽 절반, 오른쪽 절반으로 나눈 후, 합치기
		mid = (s+e) / 2;
		mergeSort(arr, s, mid);
		mergeSort(arr, mid + 1, e);
		merging(s, mid, mid + 1, e);

	+ merging(s, mid, mid + 1, e):
	  왼쪽 절반과 오른쪽 절반을 합쳐 정렬된 배열로 만드는 함수
*/

// 왼쪽 절반과 오른쪽 절반을 합쳐 정렬된 배열로 만드는 함수
void merging(int arr[], int s1, int e1, int s2, int e2)
{
	int p = s1; // 왼쪽 절반의 최소값
	int q = s2; // 오른쪽 절반의 최소값

	// arr에 정렬된 결과를 업데이트하면 값이 덮어씌워져 복잡
	// tmp 배열에 정렬한 후, arr에 정렬된 결과 복사
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

	// s1 ~ e2까지 tmp의 값을 복사
	// tmp배열은 0번부터 정렬해서 넣었기 때문에 i에서 s1만큼을 뺌
	for (int i = s1; i <= e2; i++)
		arr[i] = tmp[i - s1];
}

void mergeSort(int arr[], int s, int e)
{
	if (s >= e) return;
	
	// 1조각이 될 때까지, 계속 절반으로 나눔
	int mid = (s + e) / 2;
	mergeSort(arr, s, mid);
	mergeSort(arr, mid + 1, e);
	
	// arr[s ~ mid], arr[mid+1 ~ e]는 정렬이 된 상태
	// 처음 merging 들어갈 때는, 2조각일 때 !
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