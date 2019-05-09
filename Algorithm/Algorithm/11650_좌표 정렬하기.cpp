#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int MAX = 100005;

int N;
pair<int, int> pairs[MAX];

bool compare(pair<int, int> a, pair<int, int> b)
{
	if		(a.first > b.first) return false;
	else if (a.first == b.first)
	{
		if (a.second > b.second) return false;
		else return true;
	}
	else return true;
}

int main()
{
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d %d", &pairs[i].first, &pairs[i].second);
	sort(&pairs[0], &pairs[N], compare);
	for (int i = 0; i < N; i++)
		printf("%d %d\n", pairs[i].first, pairs[i].second);
	return 0;
}