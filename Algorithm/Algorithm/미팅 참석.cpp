#include <stdio.h>
#include <algorithm>
using namespace std;

const int MAX = 100001;

int n;
pair<int, int> meeting[MAX];

bool compare(pair<int, int> a, pair<int, int> b)
{
	if (a.second > b.second) return false;
	return true;
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d %d", &meeting[i].first, &meeting[i].second);

	/* 빨리 끝나는 순서대로 회의 진행 */
	sort(&meeting[0], &meeting[n], compare);

	int answer = 1;
	int finTime = meeting[0].second;
	
	for (int i = 1; i < n; i++)
	{
		if (meeting[i].first >= finTime)
		{
			answer++;
			finTime = meeting[i].second;
		}
	}
	printf("%d\n", answer);

	return 0;
}