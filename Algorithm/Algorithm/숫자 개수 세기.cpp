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
		if (arr[p] < arr[q])
			tmp.push_back(arr[p++]);
		else
			tmp.push_back(arr[q++]);
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
int n, q;
int cnt;
void binarySearch(int arr[], int s, int e, int v)
{
	if (s > e) return;
	if (s < 0 || s >= n || e < 0 || e >= n) return;

	int mid = (s + e) / 2;

	if (arr[mid] == v)
	{
		cnt++;
		binarySearch(arr, mid + 1, e, v);
		binarySearch(arr, s, mid - 1, v);
		return;
	}

	if (arr[mid] < v) binarySearch(arr, mid + 1, e, v);
	else             binarySearch(arr, s, mid - 1, v);
}

int main()
{
	scanf("%d %d\n", &n, &q);

	int arr[100005];
	for (int i = 0; i < n; i++)
		scanf("%d", &arr[i]);

	mergeSort(arr, 0, n - 1);

	while (q--)
	{
		int v;
		scanf("%d", &v);

		cnt = 0;
		binarySearch(arr, 0, n - 1, v);
		printf("%d\n", cnt);
	}

	return 0;
}