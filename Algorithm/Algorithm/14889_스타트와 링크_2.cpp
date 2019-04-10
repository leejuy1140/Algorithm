#include <iostream>

const int MAX = 21;
const int INF = 99999999;

bool check[MAX]; // 스타트팀 true 체크.
int n, graph[MAX][MAX], answer = INF;

/* 스타트팀의 팀원을 구해, 링크 팀과의 차이 갱신. */
void FindStartTeam(int idx, int cnt)
{
	if (cnt == n / 2) // 팀 다 구했으면, 점수 계산.
	{
		int start = 0, link = 0;
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				if (check[i] && check[j])   start += graph[i][j];
				if (!check[i] && !check[j]) link += graph[i][j];
			}
		}
		int gap = start - link;
		if (gap < 0) gap *= -1;
		answer = answer < gap ? answer : gap;
		return;
	}

	for (int i = idx + 1; i <= n; i++)
	{
		check[i] = true;
		FindStartTeam(i, cnt + 1);
		check[i] = false;
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			scanf("%d", &graph[i][j]);
	for (int i = 1; i <= n; i++)
	{
		check[i] = true;
		FindStartTeam(i, 1);
		check[i] = false;
	}
	printf("%d", answer);
	return 0;
}