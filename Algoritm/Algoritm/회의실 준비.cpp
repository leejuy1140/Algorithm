#include <stdio.h>
#include <algorithm>
#include <queue>
using namespace std;

const int MAX = 100005;

int main()
{
	int n;
	pair<int, int> data[MAX];

	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d %d", &data[i].first, &data[i].second);

	sort(&data[0], &data[n]); // 빨리 시작하는 순

	int answer = 0;
	vector<char> fin(n);
	for (int i = 0; i < n; i++)
	{
		int cnt = answer;
		for (int j = 0; j < i; j++)
		{
			if (fin[j] && data[j].second <= data[i].first)
			{
				fin[j] = 0;
				cnt--;
				break;
			}
		}
		fin[i] = 1;
		cnt++;
		answer = max(answer, cnt);
	}
	printf("%d\n", answer);

	return 0;
}