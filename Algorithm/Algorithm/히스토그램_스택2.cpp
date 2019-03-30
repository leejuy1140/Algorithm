#include <stdio.h>
#include <stack>
using namespace std;
const int MAX = 100001;
int main()
{
	int n;
	scanf("%d", &n);

	int hist[MAX];
	for (int i = 0; i < n; i++)
		scanf("%d", &hist[i]);
	hist[n] = 0; // ������ ������ ���� ����.

	stack<int> st;
	int maxArea = 0;

	// ���ʺ��� ���ÿ� �����鼭 width�� ����.
	for (int i = 0; i <= n; i++)
	{
		// i�� top���� ���� ���̶��,
		while (!st.empty() && hist[st.top()] > hist[i])
		{
			int height, left, right, width, area;
			height = hist[st.top()];

			// i�� ó������ top���� �������� �����̹Ƿ�, i �ٷ� �������� top�� ������ ���� !
			right = i - 1;

			// ���� ������ ���� ������ ���ϱ� ����, pop�� ��.
			// pop ���� top�� ���� ���̺��� ó������ ���ų� �۾����� �����̹Ƿ�,
			// ���� ������ �ٷ� �� �������� !
			st.pop();

			// pop ��, ������ ����ٸ�, ���� ���̰� ��ü �� ���� ���� ������, ó������ !
			if (st.empty()) left = 0;
			else			left = st.top() + 1;
			
			width = right - left + 1;
			area = height * width;
			maxArea = maxArea > area ? maxArea : area;
		}

		// 1. ������ ���������, push
		// 2. top���� ������, push (right ���� ����)
		st.push(i);
	}

	printf("%d\n", maxArea);
	
	return 0;
}