#include <stdio.h>
#include <algorithm>
using namespace std;

const int MAX = 100001;

int n, hist[MAX];

int histogram(int s, int e)
{
	// ����: �� ĭ���� �ɰ�����, ��ȯ
	if (s == e) return hist[s];

	int mid = (s + e) / 2;
	int maxArea = max(histogram(s, mid), histogram(mid + 1, e));

	/* mid �������� ���ʰ� �����ʿ��� ���� ū �簢���� ���ߴٸ�,
	   mid�� �����ִ� �簢���� ���ؾ� ��.
	   ���ʰ� ������ ��, �� ū ���̸� ���� �̵� !                */
	int left = mid;
	int right = mid + 1;

	// ���̴� ���� ������ ���� ���� ���̰� ����.
	int height = min(hist[left], hist[right]);
	int width = right - left + 1;
	int midArea = height * width;
	maxArea = max(midArea, maxArea);

	while (1)
	{
		if (left <= s && right >= e) break;

		// 1. left-1�� ���� �ȿ� �����ϰ�, �� ���ų�.
		// 2. right+1�� �������� �ʴ´ٸ�.
		// �������� �̵� !
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