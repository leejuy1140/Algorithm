#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

const int MAX = 5001;

int n, m, busCnt;	// 행, 열.
int sx, sy, dx, dy; // x: 열, y 행.
struct Info { int x, y, bus, cnt; };

bool visited[MAX];	// 같은 버스 또 탈 일 없음 !!!
struct Bus { int sx, sy, dx, dy; } bus[MAX];

/* 현재 위치에서 busNum의 버스로 환승 가능 여부 반환. */
bool canTranfer(int x, int y, int busNum)
{
	if (bus[busNum].sx == bus[busNum].dx) // 상하 노선.
	{
		if (bus[busNum].sx == x)
		{
			int minimum = min(bus[busNum].sy, bus[busNum].dy);
			int maximum = max(bus[busNum].sy, bus[busNum].dy);
			if (y >= minimum && y <= maximum) return true;
		}
	}
	else								  // 좌우 노선.
	{
		if (bus[busNum].sy == y)
		{
			int minimum = min(bus[busNum].sx, bus[busNum].dx);
			int maximum = max(bus[busNum].sx, bus[busNum].dx);
			if (x >= minimum && x <= maximum) return true;
		}
	}
	return false;
}

/* (sx, sy)에서 (dx, dy)로 가는 최소의 버스 수 반환. */
int TakingBus()
{
	// 시작점에서 탈 수 있는 버스 전부 큐에 삽입.
	queue<Info> q;
	for (int k = 1; k <= busCnt; k++)
	{
		if (canTranfer(sx, sy, k))
		{
			q.push({ sx, sy, k, 1 });
			visited[k] = true;
		}
	}

	while (!q.empty())
	{
		Info cur = q.front();
		q.pop();
		//printf("(%d, %d), %d -> %d\n", cur.x, cur.y, cur.bus, cur.cnt);
		// 현재 버스로 목적지 도달 가능하면, 버스 개수 반환.
		if (canTranfer(dx, dy, cur.bus)) return cur.cnt;

		// 버스 노선대로 이동.
		if (bus[cur.bus].sx == bus[cur.bus].dx) // 상하 노선.
		{ 
			int start = min(bus[cur.bus].sy, bus[cur.bus].dy);
			int end = max(bus[cur.bus].sy, bus[cur.bus].dy);

			for (int i = start; i <= end; i++)
			{
				for (int k = 1; k <= busCnt; k++)
				{
					// 탑승한 적 없는 버스이고 환승 가능하다면, 큐에 삽입.
					if (visited[k]) continue;
					if (!canTranfer(cur.x, i, k)) continue;

					q.push({ cur.x, i, k, cur.cnt + 1 });
					visited[k] = true;
				}
			}
		}
		else								 // 좌우 노선.
		{
			int start = min(bus[cur.bus].sx, bus[cur.bus].dx);
			int end = max(bus[cur.bus].sx, bus[cur.bus].dx);

			for (int i = start; i <= end; i++)
			{
				for (int k = 1; k <= busCnt; k++)
				{
					// 탑승한 적 없는 버스이고 환승 가능하다면, 큐에 삽입.
					if (visited[k]) continue;
					if (!canTranfer(i, cur.y, k)) continue;

					q.push({ i, cur.y, k, cur.cnt + 1 });
					visited[k] = true;
				}
			}
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