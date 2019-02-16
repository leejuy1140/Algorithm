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

	/* ���� ������ ������ ����. */
	sort(&job[0], &job[n], compare);

	/* dp[cur]: ���� �˹ٰ� ������ �ð��� �ִ� ���� */
	int dp[MAX];
	for (int cur = 0; cur < n; cur++)
	{
		/* ���� �˹ٺ��� ������ ������ �˹ٸ� �ϰ�, ���� �˹ٸ� ������ �� ������,
		   ���� �˹� �� �ִ� ������ ���� �˹ٸ� ����.							  */
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