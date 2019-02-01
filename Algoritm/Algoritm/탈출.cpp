#include <stdio.h>
#include <queue>
using namespace std;

const int MAX = 55;
enum { BLANK = 1000, WATER, STONE, D, S };

int n, m;
int map[MAX][MAX];
bool visited[MAX][MAX];
int dir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

struct INFO
{ 
	int r, c, time;
	void setInfo(int _r, int _c, int _time)
	{ r = _r; c = _c; time = _time; }
};

void makeFlood(int _r, int _c, int _time)
{
	INFO first;
	first.setInfo(_r, _c, _time);

	queue<INFO> q;
	q.push(first);
	map[first.r][first.c] = first.time;

	while (!q.empty())
	{
		INFO cur = q.front();
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			INFO next;
			next.setInfo(cur.r + dir[i][0], cur.c + dir[i][1], cur.time + 1);
			
			if (next.r < 0 || next.c < 0 || next.r >= n || next.c >= m) continue;
			int data = map[next.r][next.c];
			if (data == D || data == STONE || data == WATER) continue;
			if (data != BLANK && data != S) if (data <= next.time) continue;
			
			q.push(next);
			map[next.r][next.c] = next.time;
		}
	}
}

int escape(INFO first)
{
	queue<INFO> q;
	q.push(first);
	visited[first.r][first.c] = 1;

	while (!q.empty())
	{
		INFO cur = q.front();
		q.pop();

		if (map[cur.r][cur.c] == D) return cur.time;

		for (int i = 0; i < 4; i++)
		{
			INFO next;
			next.setInfo(cur.r + dir[i][0], cur.c + dir[i][1], cur.time + 1);
			
			if (next.r < 0 || next.c < 0 || next.r >= n || next.c >= m) continue;
			if (map[next.r][next.c] == STONE || visited[next.r][next.c]) continue;
			if (map[next.r][next.c] != BLANK && map[next.r][next.c] <= next.time) continue;
			
			q.push(next);
			visited[next.r][next.c] = 1;
		}
	}
	return -999;
}

int main()
{
	scanf("%d %d", &n, &m);

	INFO start;
	for (int i = 0; i < n; i++)
	{
		getchar();
		for (int j = 0; j < m; j++)
		{
			scanf("%1c", &map[i][j]);
			if (map[i][j] == 'X') map[i][j] = STONE;
			if (map[i][j] == '*') map[i][j] = WATER;
			if (map[i][j] == '.') map[i][j] = BLANK;
			if (map[i][j] == 'D') map[i][j] = D;
			if (map[i][j] == 'S')
			{ map[i][j] = S; start.setInfo(i, j, 0); }
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			if (map[i][j] == WATER)	makeFlood(i, j, 0);
	}

	int res = escape(start);
	if (res == -999) printf("KAKTUS\n");
	else			 printf("%d\n", res);

	return 0;
}