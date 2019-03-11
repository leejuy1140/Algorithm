#include <iostream>
#include <queue>
using namespace std;

const int MAX = 55;
const int INF = 99999999;

char map[MAX][MAX];
int dist[MAX][MAX][2]; // 최저, 최고 높이 저장.
int n, houseCnt, height[MAX][MAX];
int dr[8] = { -1, 1, 0, 0, -1, -1, 1, 1 };
int dc[8] = { 0, 0, -1, 1, 1, -1, 1, -1 };

struct PostOfficer { int r, c, highest, lowest, fatigue; };

bool operator>(const PostOfficer &a, const PostOfficer &b) {
	return a.fatigue > b.fatigue;
}

inline int max(int a, int b) {
	return a > b ? a : b;
}

inline int min(int a, int b) {
	return a < b ? a : b;
}

void bfs(int _r, int _c)
{
	priority_queue<PostOfficer, vector<PostOfficer>, greater<PostOfficer>> pq;
	pq.push({ _r, _c, height[_r][_c], height[_r][_c], 0 });
	dist[_r][_c][0] = height[_r][_c];
	dist[_r][_c][1] = height[_r][_c];

	while (!pq.empty())
	{
		PostOfficer cur = pq.top();
		pq.pop();
		//printf("(%d, %d) %d %d -> %d\n", cur.r, cur.c, cur.highest, cur.lowest, cur.fatigue);

		for (int i = 0; i < 8; i++)
		{
			PostOfficer next = cur;
			next.r += dr[i];
			next.c += dc[i];
			if (next.r < 0 || next.c < 0 || next.r >= n || next.c >= n) continue;
			if (map[next.r][next.c] == 'P') continue;

			next.lowest = min(next.lowest, height[next.r][next.c]);
			next.highest = max(next.highest, height[next.r][next.c]);
			next.fatigue = next.highest - next.lowest;

			if (dist[next.r][next.c][0] == next.lowest)
				if(dist[next.r][next.c][1] == next.highest) continue;
			
			if (dist[next.r][next.c][0] && dist[next.r][next.c][1])
			{
				int fatigue = dist[next.r][next.c][1] - dist[next.r][next.c][0];
				if (fatigue < next.fatigue) continue;
				if (fatigue == next.fatigue)
				{
					if (next.lowest < dist[next.r][next.c][0])
						if (next.highest > dist[next.r][next.c][1])
							continue;
				}
			}

			pq.push(next);
			dist[next.r][next.c][0] = next.lowest;
			dist[next.r][next.c][1] = next.highest;
		}
	}
	
	printf("\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			printf("%d ", dist[i][j][0]);
		printf("\n");
	}
	printf("\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			printf("%d ", dist[i][j][1]);
		printf("\n");
	}
}

int main()
{
	int post_r, post_c;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		getchar();
		for (int j = 0; j < n; j++)
		{
			scanf("%1c", &map[i][j]);
			if (map[i][j] == 'P')
			{
				post_r = i;
				post_c = j;
			}
			if (map[i][j] == 'K') houseCnt++;
		}
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			scanf("%d", &height[i][j]);

	bfs(post_r, post_c);

	int highest = 0, lowest = INF;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (map[i][j] == 'K')
			{
				lowest = min(lowest, dist[i][j][0]);
				highest = max(highest, dist[i][j][1]);
			}
		}
	}
	printf("%d", highest - lowest);

	return 0;
}