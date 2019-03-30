#include <stdio.h>
#include <algorithm>
using namespace std;

const int MAX = 100010;

int n, num[MAX];

/* num의 s ~ e의 구간 중 연속 부분 최대합을 반환. */
int solution(int s, int e)
{
	if (s >= e) return num[s];

	int mid = (s + e) / 2;
	int leftSectionMax = solution(s, mid);
	int rightSectionMax = solution(mid + 1, e);

	/* 중간부터 왼쪽, 오른쪽으로 뻗어나감. (구간 주의 !) */
	int sum = num[mid];
	int leftMidSectionMax = sum;
	for (int i = mid - 1; i >= s; i--)
	{
		sum += num[i];
		if (sum > leftMidSectionMax) leftMidSectionMax = sum;
	}

	sum = num[mid + 1];
	int rightMidSectionMax = sum;
	for (int i = mid + 2; i <= e; i++)
	{
		sum += num[i];
		if (sum > rightMidSectionMax) rightMidSectionMax = sum;
	}

	int midSectionMax = leftMidSectionMax + rightMidSectionMax;
	
	int ret = leftSectionMax > rightSectionMax ? leftSectionMax : rightSectionMax;
	return ret = ret > midSectionMax ? ret : midSectionMax;
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &num[i]);

	printf("%d\n", solution(0, n - 1));
	return 0;
}