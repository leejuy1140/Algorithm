#include <stdio.h>
#include <algorithm>
using namespace std;

const int MAX = 100001;

int n, hist[MAX];

int histogram(int s, int e)
{
	// 기저: 한 칸으로 쪼개지면, 반환
	if (s == e) return hist[s];

	int mid = (s + e) / 2;
	int maxArea = max(histogram(s, mid), histogram(mid + 1, e));

	/* mid 기준으로 왼쪽과 오른쪽에서 가장 큰 사각형을 구했다면,
	   mid에 걸쳐있는 사각형을 구해야 함.
	   왼쪽과 오른쪽 중, 더 큰 높이를 향해 이동 !                */
	int left = mid;
	int right = mid + 1;

	// 높이는 범위 내에서 가장 낮은 높이가 기준.
	int height = min(hist[left], hist[right]);
	int width = right - left + 1;
	int midArea = height * width;
	maxArea = max(midArea, maxArea);

	while (1)
	{
		if (left <= s && right >= e) break;

		// 1. left-1이 범위 안에 존재하고, 더 높거나.
		// 2. right+1이 존재하지 않는다면.
		// 왼쪽으로 이동 !
		if ((left > s && hist[left - 1] > hist[right + 1]) || right >= e)
			height = min(hist[--left], height);
		else
			height = min(hist[++right], height);

		width = right - left + 1;
		midArea = height * width;
		maxArea = max(midArea, maxArea);
	}
	return maxArea;
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &hist[i]);

	int answer = histogram(0, n - 1);
	printf("%d\n", answer);

	return 0;
}