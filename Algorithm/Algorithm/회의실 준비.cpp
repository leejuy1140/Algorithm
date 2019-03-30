#include <stdio.h>
#include <algorithm>
#include <queue>
using namespace std;

const int MAX = 200005;

int n;
pair<int, int> meeting[MAX];

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d %d", &meeting[i].first, &meeting[i].second);

	/* 시작 시간 순으로 정렬 */
	sort(&meeting[0], &meeting[n]);

	/* 빨리 끝나는 순으로 회의실 처리 */
	priority_queue<int, vector<int>, greater<int>> pq;
	for (int i = 0; i < n; i++)
	{
		if (pq.size() && pq.top() <= meeting[i].first) pq.pop();
		pq.push(meeting[i].second);
	}
	printf("%d\n", pq.size());

	return 0;
}