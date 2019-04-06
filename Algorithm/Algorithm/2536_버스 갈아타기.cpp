#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

const int MAX = 5001;

int n, m, busCnt;	// ��, ��.
int sx, sy, dx, dy; // x: ��, y ��.
struct Info { int x, y, bus, cnt; };

bool visited[MAX];	// ���� ���� �� Ż �� ���� !!!
struct Bus { int sx, sy, dx, dy; } bus[MAX];

/* ���� ��ġ���� busNum�� ������ ȯ�� ���� ���� ��ȯ. */
bool canTranfer(int x, int y, int busNum)
{
	if (bus[busNum].sx == bus[busNum].dx) // ���� �뼱.
	{
		if (bus[busNum].sx == x)
		{
			int minimum = min(bus[busNum].sy, bus[busNum].dy);
			int maximum = max(bus[busNum].sy, bus[busNum].dy);
			if (y >= minimum && y <= maximum) return true;
		}
	}
	else								  // �¿� �뼱.
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

/* (sx, sy)���� (dx, dy)�� ���� �ּ��� ���� �� ��ȯ. */
int TakingBus()
{
	// ���������� Ż �� �ִ� ���� ���� ť�� ����.
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
		// ���� ������ ������ ���� �����ϸ�, ���� ���� ��ȯ.
		if (canTranfer(dx, dy, cur.bus)) return cur.cnt;

		// ���� �뼱��� �̵�.
		if (bus[cur.bus].sx == bus[cur.bus].dx) // ���� �뼱.
		{ 
			int start = min(bus[cur.bus].sy, bus[cur.bus].dy);
			int end = max(bus[cur.bus].sy, bus[cur.bus].dy);

			for (int i = start; i <= end; i++)
			{
				for (int k = 1; k <= busCnt; k++)
				{
					// ž���� �� ���� �����̰� ȯ�� �����ϴٸ�, ť�� ����.
					if (visited[k]) continue;
					if (!canTranfer(cur.x, i, k)) continue;

					q.push({ cur.x, i, k, cur.cnt + 1 });
					visited[k] = true;
				}
			}
		}
		else								 // �¿� �뼱.
		{
			int start = min(bus[cur.bus].sx, bus[cur.bus].dx);
			int end = max(bus[cur.bus].sx, bus[cur.bus].dx);

			for (int i = start; i <= end; i++)
			{
				for (int k = 1; k <= busCnt; k++)
				{
					// ž���� �� ���� �����̰� ȯ�� �����ϴٸ�, ť�� ����.
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