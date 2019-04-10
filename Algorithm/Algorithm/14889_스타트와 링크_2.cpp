#include <iostream>

const int MAX = 21;
const int INF = 99999999;

bool check[MAX]; // ��ŸƮ�� true üũ.
int n, graph[MAX][MAX], answer = INF;

/* ��ŸƮ���� ������ ����, ��ũ ������ ���� ����. */
void FindStartTeam(int idx, int cnt)
{
	if (cnt == n / 2) // �� �� ��������, ���� ���.
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