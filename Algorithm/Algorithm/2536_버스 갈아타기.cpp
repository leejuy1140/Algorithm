#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

const int MAX = 5001;

int n, m, busCnt;	// 행, 열.
int sx, sy, dx, dy; // x: 열, y 행.
struct Info { int bus, cnt; };

bool visited[MAX]; // 같은 버스 또 탈 일 없음 !!!
struct Bus { int sx, sy, dx, dy; } bus[MAX];

/* 현재 버스에서 (x, y)로 갈 수 있는지 반환. */
bool CanTake(int x, int y, Bus cur)
{
	if (cur.sx == cur.dx) // 상하 노선.
	{
		if (cur.sx == x)
		{
			int minimum = min(cur.sy, cur.dy);
			int maximum = max(cur.sy, cur.dy);
			if (y >= minimum && y <= maximum) return true;
		}
	}
	else				  // 좌우 노선.
	{
		if (cur.sy == y)
		{
			int minimum = min(cur.sx, cur.dx);
			int maximum = max(cur.sx, cur.dx);
			if (x >= minimum && x <= maximum) return true;
		}
	}
	return false;
}

/* 현재 버스에서 nextBus로 환승할 수 있는지 반환. */
bool canTranfer(Bus cur, Bus next)
{
	if (cur.sx == cur.dx) /* 현재 버스가 상하 노선. (현재 x 일정) */
	{
		int cur_start = min(cur.sy, cur.dy);
		int cur_end = max(cur.sy, cur.dy);

		if (next.sx == next.dx) // 다음 버스도 상하 노선. (다음 x 일정)
		{
			int next_start = min(next.sy, next.dy);
			int next_end = max(next.sy, next.dy);

			if		(cur.sx != next.sx)    return false;
			else if	(cur_end < next_start) return false;
			else if (cur_start > next_end) return false;
			else						   return true;
		}
		else					// 다음 버스가 좌우 노선. (다음 y 일정)
		{
			int next_start = min(next.sx, next.dx);
			int next_end = max(next.sx, next.dx);

			if (next.sy >= cur_start && next.sy <= cur_end)
			{
				if (cur.sx >= next_start && cur.sx <= next_end) return true;
				else return false;
			}
			else return false;
		}
	}
	else /* 현재 버스가 좌우 노선. (현재 y 일정) */
	{
		int cur_start = min(cur.sx, cur.dx);
		int cur_end = max(cur.sx, cur.dx);

		if (next.sx == next.dx) // 다음 버스가 상하 노선. (다음 x 일정)
		{
			int next_start = min(next.sy, next.dy);
			int next_end = max(next.sy, next.dy);

			if (next.sx >= cur_start && next.sx <= cur_end)
			{
				if (cur.sy >= next_start && cur.sy <= next_end) return true;
				else return false;
			}
			else return false;
		}
		else					// 다음 버스도 좌우 노선. (다음 y 일정)
		{
			int next_start = min(next.sx, next.dx);
			int next_end = max(next.sx, next.dx);

			if		(cur.sy != next.sy)    return false;
			else if (cur_end < next_start) return false;
			else if (cur_start > next_end) return false;
			else						   return true;
		}
	}
	return true;
}

/* (sx, sy)에서 (dx, dy)로 가는 최소 버스 수 반환. */
int TakingBus()
{
	// 시작점에서 탈 수 있는 버스 전부 큐에 삽입.
	queue<pair<int, int>> q;
	for (int k = 1; k <= busCnt; k++)
	{
		if (CanTake(sx, sy, bus[k]))
		{
			q.push(make_pair(k, 1)); // 버스, 버스 탄 횟수
			visited[k] = true;
		}
	}

	while (!q.empty())
	{
		int curBus = q.front().first;
		int curCnt = q.front().second;
		q.pop();
		
		// 현재 버스로 목적지 도달 가능하면, 버스 개수 반환.
		if (CanTake(dx, dy, bus[curBus])) return curCnt;

		// 다음 버스로 이동 가능한지 체크.
		for (int k = 1; k <= busCnt; k++)
		{
			// 탑승한 적 없는 버스이고 환승 가능하다면, 큐에 삽입.
			if (visited[k]) continue;
			if (!canTranfer(bus[curBus], bus[k])) continue;

			q.push(make_pair(k, curCnt + 1));
			visited[k] = true;
		}
	}
}

int main()
{
	scanf("%d %d", &m, &n);
	scanf("%d", &busCnt);
	for (int i = 0; i < busCnt; i++)
	{
		int idx;
		scanf("%d", &idx);
		scanf("%d %d", &bus[idx].sx, &bus[idx].sy);
		scanf("%d %d", &bus[idx].dx, &bus[idx].dy);
	}
	scanf("%d %d %d %d", &sx, &sy, &dx, &dy);

	int answer = TakingBus();
	printf("%d", answer);

	return 0;
}