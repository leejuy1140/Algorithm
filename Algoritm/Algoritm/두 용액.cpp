#include <stdio.h>
#include <algorithm>
using namespace std;

void binarySearch(int arr[], int s, int e, int v, int &minDiff, int minValue[])
{
	if (s > e) return;

	int mid = (s + e) / 2;

	if (arr[mid] == v)
		return binarySearch(arr, mid + 1, e, v, minDiff, minValue);

	int sum = arr[mid] + v;
	int mini = min(arr[mid], v);
	int maxi = max(arr[mid], v);

	if (abs(minDiff) == abs(sum) && minValue[0] > mini)
	{
		minValue[0] = mini;
		minValue[1] = maxi;
	}
	if (abs(minDiff) > abs(sum))
	{
		minDiff = sum;
		minValue[0] = mini;
		minValue[1] = maxi;
	}

	if (arr[mid] > abs(v)) binarySearch(arr, s, mid - 1, v, minDiff, minValue);
	else			       binarySearch(arr, mid + 1, e, v, minDiff, minValue);
}

int main()
{
	int n;
	scanf("%d", &n);

	int arr[100005];
	for (int i = 0; i < n; i++)
		scanf("%d", &arr[i]);

	sort(&arr[0], &arr[n - 1]);

	int minDiff = 2000000000;
	int minValue[2] = { 2000000000, 2000000000 };
	for (int i = 0; i < n; i++)
		binarySearch(arr, 0, n - 1, arr[i], minDiff, minValue);

	printf("%d %d", minValue[0], minValue[1]);

	return 0;
}