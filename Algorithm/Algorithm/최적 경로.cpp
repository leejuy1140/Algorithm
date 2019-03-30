#include <iostream>
#include <algorithm>
using namespace std;

const int MAX = 12;
const int INF = 99999999;

int n, dist[MAX][MAX];
struct Point { int r, c; } p[MAX];

// 위치, 방문 여부 비트 (int이므로 32개까지 체크 가능).
// 해당 위치에서, 방문 여부 비트에 체크된 위치를 순회했을 때, 최소 거리.
int cache[MAX][1 << MAX];

int tsp(int cur, int visited)
{	
	// 고객 전부 방문했으면, 집으로 돌아감.
	// (n이 5라면, 1000000 - 1 = 0111111.
	// MSB는 집이므로, 집을 제외한 고객 전부 방문 완료.)
	if (visited == (1 << n + 1) - 1) return dist[cur][n + 1];
	
	// 계산했던 최적값이 있다면, 사용.
	int &ret = cache[cur][visited];
	if (ret != -1) return ret;

	ret = INF; // 최적값 계산.
	for (int next = 1; next <= n; next++)
	{
		// 방문한적 있다면, 패스.
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
		
		// 1. 거리 미리 계산 및 캐시 초기화.
		for (int i = 0; i < n + 2; i++)
			for (int j = 0; j < n + 2; j++)
				dist[i][j] = abs(p[i].r - p[j].r) + abs(p[i].c - p[j].c);
		memset(cache, -1, sizeof(cache));

		// 2. 순회.
		int answer = tsp(0, 1 << 0);
		printf("#%d %d\n", T, answer);
	}
	return 0;
}