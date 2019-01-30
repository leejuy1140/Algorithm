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
	hist[n] = 0; // 스택을 완전히 비우기 위해.

	stack<int> st;
	int maxArea = 0;

	// 왼쪽부터 스택에 넣으면서 width를 구함.
	for (int i = 0; i <= n; i++)
	{
		// i가 top보다 낮은 높이라면,
		while (!st.empty() && hist[st.top()] > hist[i])
		{
			int height, left, right, width, area;
			height = hist[st.top()];

			// i가 처음으로 top보다 낮아지는 높이이므로, i 바로 전까지가 top의 오른쪽 범위 !
			right = i - 1;

			// 현재 높이의 왼쪽 범위를 구하기 위해, pop을 함.
			// pop 후의 top이 현재 높이보다 처음으로 같거나 작아지는 높이이므로,
			// 왼쪽 범위는 바로 그 다음부터 !
			st.pop();

			// pop 후, 스택이 비었다면, 현재 높이가 전체 중 가장 낮은 것으로, 처음부터 !
			if (st.empty()) left = 0;
			else			left = st.top() + 1;
			
			width = right - left + 1;
			area = height * width;
			maxArea = maxArea > area ? maxArea : area;
		}

		// 1. 스택이 비어있으면, push
		// 2. top보다 높으면, push (right 범위 증가)
		st.push(i);
	}

	printf("%d\n", maxArea);
	
	return 0;
}