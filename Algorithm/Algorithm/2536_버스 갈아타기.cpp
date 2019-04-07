#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

const int MAX = 5001;

int n, m, busCnt;	// ��, ��.
int sx, sy, dx, dy; // x: ��, y ��.
struct Info { int bus, cnt; };

bool visited[MAX]; // ���� ���� �� Ż �� ���� !!!
struct Bus { int sx, sy, dx, dy; } bus[MAX];

/* ���� �������� (x, y)�� �� �� �ִ��� ��ȯ. */
bool CanTake(int x, int y, Bus cur)
{
	if (cur.sx == cur.dx) // ���� �뼱.
	{
		if (cur.sx == x)
		{
			int minimum = min(cur.sy, cur.dy);
			int maximum = max(cur.sy, cur.dy);
			if (y >= minimum && y <= maximum) return true;
		}
	}
	else				  // �¿� �뼱.
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

/* ���� �������� nextBus�� ȯ���� �� �ִ��� ��ȯ. */
bool canTranfer(Bus cur, Bus next)
{
	if (cur.sx == cur.dx) /* ���� ������ ���� �뼱. (���� x ����) */
	{
		int cur_start = min(cur.sy, cur.dy);
		int cur_end = max(cur.sy, cur.dy);

		if (next.sx == next.dx) // ���� ������ ���� �뼱. (���� x ����)
		{
			int next_start = min(next.sy, next.dy);
			int next_end = max(next.sy, next.dy);

			if		(cur.sx != next.sx)    return false;
			else if	(cur_end < next_start) return false;
			else if (cur_start > next_end) return false;
			else						   return true;
		}
		else					// ���� ������ �¿� �뼱. (���� y ����)
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
	else /* ���� ������ �¿� �뼱. (���� y ����) */
	{
		int cur_start = min(cur.sx, cur.dx);
		int cur_end = max(cur.sx, cur.dx);

		if (next.sx == next.dx) // ���� ������ ���� �뼱. (���� x ����)
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
		else					// ���� ������ �¿� �뼱. (���� y ����)
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

/* (sx, sy)���� (dx, dy)�� ���� �ּ� ���� �� ��ȯ. */
int TakingBus()
{
	// ���������� Ż �� �ִ� ���� ���� ť�� ����.
	queue<pair<int, int>> q;
	for (int k = 1; k <= busCnt; k++)
	{
		if (CanTake(sx, sy, bus[k]))
		{
			q.push(make_pair(k, 1)); // ����, ���� ź Ƚ��
			visited[k] = true;
		}
	}

	while (!q.empty())
	{
		int curBus = q.front().first;
		int curCnt = q.front().second;
		q.pop();
		
		// ���� ������ ������ ���� �����ϸ�, ���� ���� ��ȯ.
		if (CanTake(dx, dy, bus[curBus])) return curCnt;

		// ���� ������ �̵� �������� üũ.
		for (int k = 1; k <= busCnt; k++)
		{
			// ž���� �� ���� �����̰� ȯ�� �����ϴٸ�, ť�� ����.
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