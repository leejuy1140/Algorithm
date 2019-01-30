#include <stdio.h>
#include <algorithm>
using namespace std;

const int MAX = 100010;

int main()
{
	int n, num[MAX], dp[MAX];
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &num[i]);

/*
	이전과의 차이점
	카드 놀이는 연속의 최대 개수가 제한됨.
	또한, 전부 자연수이므로 중간에 작아졌다가 다시 커질 가능성이 없음.
	(버튼 누르기는 카드 놀이와 동일)

	즉, 연속의 개수가 제한되어 있지 않고, 음수가 있기 때문에 복잡함.
*/

	dp[0] = num[0];
	int answer = dp[0];
	for (int i = 1; i < n; i++)
	{
		dp[i] = max(num[i], dp[i - 1] + num[i]);
		answer = max(answer, dp[i]);
	}
	printf("%d", answer);

	return 0;
}