#include <iostream>
#include <algorithm>
using namespace std;

const int MAX = 12;
const int INF = 99999999;

int n, dist[MAX][MAX];
struct Point { int r, c; } p[MAX];

// ��ġ, �湮 ���� ��Ʈ (int�̹Ƿ� 32������ üũ ����).
// �ش� ��ġ����, �湮 ���� ��Ʈ�� üũ�� ��ġ�� ��ȸ���� ��, �ּ� �Ÿ�.
int cache[MAX][1 << MAX];

int tsp(int cur, int visited)
{	
	// �� ���� �湮������, ������ ���ư�.
	// (n�� 5���, 1000000 - 1 = 0111111.
	// MSB�� ���̹Ƿ�, ���� ������ �� ���� �湮 �Ϸ�.)
	if (visited == (1 << n + 1) - 1) return dist[cur][n + 1];
	
	// ����ߴ� �������� �ִٸ�, ���.
	int &ret = cache[cur][visited];
	if (ret != -1) return ret;

	ret = INF; // ������ ���.
	for (int next = 1; next <= n; next++)
	{
		// �湮���� �ִٸ�, �н�.
		if (visited & (1 << next)) continue;
		ret = min(ret, tsp(next, visited | (1 << next)) + dist[cur][next]);
	}
	return ret;
}

int main()
{
	int t;
	scanf("%d", &t);
	for (int T = 1; T <= t; T++)
	{
		scanf("%d", &n);
		scanf("%d %d", &p[0].r, &p[0].c);
		scanf("%d %d", &p[n + 1].r, &p[n + 1].c);
		for (int i = 1; i <= n; i++)
			scanf("%d %d", &p[i].r, &p[i].c);
		
		// 1. �Ÿ� �̸� ��� �� ĳ�� �ʱ�ȭ.
		for (int i = 0; i < n + 2; i++)
			for (int j = 0; j < n + 2; j++)
				dist[i][j] = abs(p[i].r - p[j].r) + abs(p[i].c - p[j].c);
		memset(cache, -1, sizeof(cache));

		// 2. ��ȸ.
		int answer = tsp(0, 1 << 0);
		printf("#%d %d\n", T, answer);
	}
	return 0;
}