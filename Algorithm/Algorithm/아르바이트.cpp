#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;

const int MAX = 1001;

struct Job { int s, e, pay; };
Job job[MAX];

bool compare(Job a, Job b)
{
	if (a.e > b.e) return false;
	if (a.e == b.e && a.s > b.s) return false;
	return true;
}

int main()
{
	int n, answer;
	scanf("%d", &n);
	srand(time(NULL));
	for (int i = 0; i < n; i++)
		scanf("%d %d %d", &job[i].s, &job[i].e, &job[i].pay);

	/* 빨리 끝나는 순으로 정렬. */
	sort(&job[0], &job[n], compare);

	/* dp[cur]: 현재 알바가 끝나는 시간의 최대 수익 */
	int dp[MAX];
	for (int cur = 0; cur < n; cur++)
	{
		/* 현재 알바보다 이전에 끝나는 알바를 하고, 현재 알바를 수행할 수 있으면,
		   이전 알바 중 최대 수익을 만든 알바를 선택.							  */
		int maxPay = 0;
		for (int prev = 0; prev < cur; prev++)
		{
			int flag = 0;
			if (job[cur].s < job[prev].e && job[cur].s >= job[prev].s) flag = 1;
			if (job[cur].e < job[prev].e && job[cur].e >= job[prev].s) flag = 1;
			if (job[cur].s <= job[prev].s && job[cur].e >= job[prev].e) flag = 1;

			if (flag) continue;

			maxPay = maxPay > dp[prev] ? maxPay : dp[prev];
		}
		dp[cur] = maxPay + job[cur].pay;
		answer = answer > dp[cur] ? answer : dp[cur];
	}
	printf("%d\n", answer);

	return 0;
}