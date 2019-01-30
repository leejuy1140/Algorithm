#include <stdio.h>
#include <string.h>

int n, r, maxDist;
bool tree[100][100], chk[100];

void getDistance(int node, int dist)
{
	chk[node] = 1;

	for (int i = 0; i < n; i++)
	{
		if (!chk[i] && tree[node][i])
		{
			getDistance(i, dist + 1);
			chk[i] = 0;
		}
	}

	if (maxDist < dist) maxDist = dist;
	return;
}

int main()
{
	scanf("%d %d", &n, &r);
	for (int i = 0; i < n - 1; i++)
	{
		int a, b;
		scanf("%d %d", &a, &b);

		// a가 b의 부모라는 말이 아니기 때문에, 양방향으로 연결!
		// 0 1이 아닌, 1 0으로 입력이 들어올수도 있음!
		tree[a][b] = 1;
		tree[b][a] = 1;
	}

	getDistance(r, 0);
	printf("%d\n", maxDist);

	return 0;
}