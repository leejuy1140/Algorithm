#include <stdio.h>
#include <string.h>
#include <queue>
using namespace std;

const int MAX = 21;

bool visited[MAX][MAX];
int n, fishCnt, map[MAX][MAX];
int dir[4][2] = { {-1, 0}, {0, -1}, {0, 1}, {1, 0} };

struct BabyShark
{ 
	int r, c, size, eat, time;
	void set(int _r, int _c, int _s, int _e, int _t)
	{ r = _r; c = _c; size = _s; eat = _e; time = _t; }
};
BabyShark shark;

/* 현재 아기 상어 위치에서
   먹을 수 있는 물고기 위치까지의 거리를 계산하고,
   먹을 수 있는 물고기가 존재하면, 참 반환.		   */
bool bfs(int &minR, int &minC, int &minDist)
{
	queue<BabyShark> q;
	q.push(shark);
	visited[shark.r][shark.c] = 1;
	minDist = 99999999;

	bool flag = 0;
	while (!q.empty())
	{
		BabyShark cur = q.front();
		q.pop();

		/* 먹을 수 있는 위치에 도달하면, dist 설정. */
		if (map[cur.r][cur.c] && map[cur.r][cur.c] < cur.size)
		{
			flag = 1;
			bool change = 0;
			if (cur.time < minDist) change = 1;
			else if (cur.time == minDist && cur.r < minR) change = 1;
			else if (cur.time == minDist && cur.r == minR && cur.c < minC) change = 1;
			
			if (change) { minR = cur.r; minC = cur.c; minDist = cur.time; }
			continue; // 그 다음은 현재보다 가까울 수 없기 때문에, 패스.
		}

		/* 이동 위치 탐색. */
		for (int i = 0; i < 4; i++)
		{
			int nr = cur.r + dir[i][0];
			int nc = cur.c + dir[i][1];
			if (nr < 0 || nc < 0 || nr >= n || nc >= n) continue;
			if (visited[nr][nc]) continue;
			if (map[nr][nc] > cur.size) continue; // 이동 불가.
			
			BabyShark next;
			next.set(nr, nc, cur.size, cur.eat, cur.time + 1);
			q.push(next);
			visited[nr][nc] = 1;
		}
	}
	return flag;
}

int main()
{
	int minR, minC, minDist;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			scanf("%d", &map[i][j]);
			if (map[i][j] == 9)
			{
				map[i][j] = 0;
				shark.set(i, j, 2, 0, 0);
			}
			if (map[i][j] >= 1 && map[i][j] <= 6) fishCnt++;
		}
	}

	while (1)
	{
		if(!bfs(minR, minC, minDist)) break;

		/* 거리가 가장 가까운 물고기로 이동 & 먹기. */
		shark.set(minR, minC, shark.size, shark.eat + 1, minDist);
		map[minR][minC] = 0;

		/* 자신의 크기와 같은 수의 물고기를 먹었으면, 크기 증가 */
		if (shark.eat == shark.size)
		{
			shark.size++;
			shark.eat = 0;
		}
		for (int i = 0; i < n; i++)
			memset(&visited[i], 0, n);
	}
	printf("%d\n", shark.time);

	return 0;
}