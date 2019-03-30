/* ���� ���� */

#include <stdio.h>
#include <stack>
#include <algorithm>
using namespace std;

const int MAX = 100000;

int n, hist[MAX];

int histogram(int s, int e)
{
	// ����: ��� �������� ������ 1ĭ�� �� ���
	if (s == e) return hist[s];

	// 1. ���ʰ� ������ ������׷����� ū �� ã��
	int mid = (s + e) / 2;
	int ret = max(histogram(s, mid), histogram(mid + 1, e));

	// 2. mid�� �������� �������� ������� ��, ���� ũ�Ⱑ ū �� ����.
	int left = mid, right = mid + 1;

	int height = min(hist[left], hist[right]);
	int width = right - left + 1;
	ret = max(ret, height * width);

	int flag1 = 0, flag2 = 0;
	while (1)
	{
		if (left <= s) flag1 = 1;
		if (right >= e) flag2 = 1;
		if (flag1 && flag2) break;

		if ((!flag1 && hist[left - 1] > hist[right + 1]) || flag2)
			height = min(height, hist[--left]);
		else
			height = min(height, hist[++right]);

		width = right - left + 1;
		ret = max(ret, height * width);
	}
	return ret;
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