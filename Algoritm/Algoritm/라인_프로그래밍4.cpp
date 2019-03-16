#include <iostream>
#include <algorithm>
using namespace std;

const int MAX = 100001;

int n, h[MAX];
int solution(int idx)
{
	int left = 0;
	for (int i = idx - 1; i >= 0; i--)
	{
		if (h[idx] <= h[i])
		{
			left = idx - i;
			break;
		}
	}
	int right = 0;
	for (int i = idx + 1; i < n; i++)
	{
		if (h[idx] <= h[i])
		{
			right = i - idx;
			break;
		}
	}
	return left + right;
}
int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &h[i]);

	int answer = 0;
	for (int i = 0; i < n; i++)
		answer = max(answer, solution(i));
	printf("%d", answer);

	return 0;
}