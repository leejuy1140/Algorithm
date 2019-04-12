#include <stdio.h>
#include <string.h>
#include <queue>
using namespace std;

const int MAX = 21;
const int INF = 999999;

int n, map[MAX][MAX], dist[MAX][MAX];
int dir[4][2] = { {-1, 0}, {0, -1}, {0, 1}, {1, 0} };
struct Shark { int r, c, move, eat, size; };

/* ����� ���� ��ȯ. */
bool CheckFish(int num)
{
	return (num >= 1 && num <= 6);
}

/* ���� �Ʊ� ��� ��ġ���� ���������� �Ÿ� ǥ��. */
void CheckDistance(Shark baby)
{
	queue<Shark> q;
	q.push(baby);
	dist[baby.r][baby.c] = INF;

	while (!q.empty())
	{
		Shark cur = q.front();
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			int nr = cur.r + dir[i][0];
			int nc = cur.c + dir[i][1];
			if (nr < 0 || nc < 0 || nr >= n || nc >= n) continue;
			if (map[nr][nc] > cur.size) continue; // ����Ⱑ �� ũ�� �н�.
			if (dist[nr][nc]) continue;

			q.push({ nr, nc, cur.move + 1, cur.eat, cur.size });
			dist[nr][nc] = cur.move + 1;
		}
	}
}

void ShowMap(Shark baby)
{
	printf("\n*************\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			printf("%d ", dist[i][j]);
		printf("\n");
	}
	printf("\n[%d]\n", baby.size);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i == baby.r && j == baby.c) printf("9 ");
			else  printf("%d ", map[i][j]);
		}
		printf("\n");
	}
}

int main()
{
	Shark baby;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			scanf("%d", &map[i][j]);
			if (map[i][j] == 9)
			{
				baby = { i, j, 0, 0, 2 };
				map[i][j] = 0;
			}
		}
	}

	int time = 0;
	while (1) 
	{
		// 1. bfs�� ���������� �Ÿ� ǥ��.
		memset(dist, 0, sizeof(dist));
		CheckDistance(baby);

		// 2. for���� ���� ������ ���鼭, ���� �Ÿ� ���� �� ã�� �̵�.
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (!map[i][j] || !dist[i][j]) continue;
				if (dist[i][j] >= dist[baby.r][baby.c]) continue;
				if (baby.size <= map[i][j]) continue;
				baby.r = i;
				baby.c = j;
			}
		}

		// 3. �̵����� �ʾ����� ����. (����Ⱑ ���ų� ������ ����.)
		if (dist[baby.r][baby.c] == INF) break;

		// 4. ����⸦ �԰� �ð��� ũ�� ����.
		baby.eat++;
		map[baby.r][baby.c] = 0;
		if (baby.eat == baby.size)
		{
			baby.eat = 0;
			baby.size++;
		}
		time += dist[baby.r][baby.c];
	};
	printf("%d", time);

	return 0;
}
