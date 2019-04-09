#include <iostream>
#include <queue>
using namespace std;

const int MAX = 101;
const int SNAKE = 1;
const int APPLE = 2;

int n, k, l, map[MAX][MAX];
int direction[4][2] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0} }; // ¼­ºÏµ¿³²
queue<pair<int, int>> snake; // ²¿¸®ºÎÅÍ ¸Ó¸®±îÁö ¹ìÀÇ ¸öÅë ÁÂÇ¥ ÀúÀå.
queue<pair<int, char>> change; // ¹æÇâ ¹Ù²Ü ½Ã°£°ú ¹Ù²Ü ¹æÇâ ÀúÀå.

int DummyGame(int r, int c, int dir, int time)
{
	// ¹æÇâ ¹Ù²Ü ½Ã°£ÀÌ¸é, ¹Ù²Þ.
	if (!change.empty() && change.front().first == time)
	{
		if (change.front().second == 'L')
		{
			dir--;
			if (dir < 0) dir = 3;
		}
		else dir = (dir + 1) % 4;
		change.pop();
	}

	int nr = r + direction[dir][0];
	int nc = c + direction[dir][1];
	if (nr < 1 || nc < 1 || nr > n || nc > n) return time + 1;
	if (map[nr][nc] == SNAKE) return time + 1;
	
	// »ç°ú°¡ ¾Æ´Ï¸é, ²¿¸®¸¦ ÀÚ¸¥´Ù.
	if (map[nr][nc] != APPLE)
	{
		map[snake.front().first][snake.front().second] = 0;
		snake.pop();
	}
	snake.push({ nr, nc });
	map[nr][nc] = SNAKE;

	return DummyGame(nr, nc, dir, time + 1);
}

int main()
{
	scanf("%d\n%d", &n, &k);
	for (int i = 0; i < k; i++)
	{
		int a, b;
		scanf("%d %d", &a, &b);
		map[a][b] = APPLE;
	}
	scanf("%d", &l);
	for (int i = 0; i < l; i++)
	{
		int a; char b;
		scanf("%d", &a);
		getchar(); scanf("%c", &b);
		change.push({ a, b });
	}
	
	map[1][1] = SNAKE;
	snake.push({ 1, 1 });
	printf("%d", DummyGame(1, 1, 2, 0));

	return 0;
}