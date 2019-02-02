#include <stdio.h>
#include <queue>
#include <algorithm>
using namespace std;

const int MAX = 9000;
const int INF = 999999999;
const int BOTTOM = 1000;

int a, b;
bool visited[MAX], table[MAX]; // 1: 소수 X

int bfs()
{
	queue<pair<int, int>> q; // 소수, 단계
	q.push(pair<int, int>(a, 0));
	visited[a - BOTTOM] = 1;

	int minLevel = INF;
	while (!q.empty())
	{
		pair<int, int> cur = q.front();
		q.pop();

		if (cur.first == b) minLevel = min(minLevel, cur.second);

		// 어떻게 바꿀지..?
	}
	
	if (minLevel == INF) return -1;
	return minLevel;
}

int main()
{
	int t;
	scanf("%d", &t);
	
	for (int prime = 2; prime < MAX; prime++)
	{
		if (table[prime]) continue;
		for (int i = 0; i < MAX; i++)
		{
			if (!table[i] && (i + BOTTOM) == prime) continue;
			if ((i + BOTTOM) % prime == 0)			table[i] = 1;
		}
	}

	while (t--)
	{
		scanf("%d %d", a, b);
		
		int ret = bfs();
		if (ret == -1) printf("impossible\n");
		else		   printf("%d\n", ret);

		memset(visited, 0, MAX);
	}
	return 0;
}