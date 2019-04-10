#include <iostream>

const int MAX = 21;

int n, m, k, map[MAX][MAX];
int dx[5] = { 0, 0, 0, -1, 1 }; // 동서북남
int dy[5] = { 0, 1, -1, 0, 0 };
struct Dice { int x, y, u, d, l, r, f, b; } dice;

/* 주사위를 dir방향으로 굴린 후, (x, y)와 각 칸의 수 갱신.
   만약 범위를 벗어난다면, 거짓 반환.						*/
bool RollDice(int dir)
{
	// 바깥으로 이동하려한다면, 거짓 반환.
	int nx = dice.x + dx[dir];
	int ny = dice.y + dy[dir];
	if (nx < 0 || ny < 0 || nx >= n || ny >= m) return false;

	// 주사위 값 갱신.
	if (dir == 1) dice = { nx, ny, dice.l, dice.r, dice.d, dice.u, dice.f, dice.b };
	if (dir == 2) dice = { nx, ny, dice.r, dice.l, dice.u, dice.d, dice.f, dice.b };
	if (dir == 3) dice = { nx, ny, dice.f, dice.b, dice.l, dice.r, dice.d, dice.u };
	if (dir == 4) dice = { nx, ny, dice.b, dice.f, dice.l, dice.r, dice.u, dice.d };
	return true;
}

int main()
{
	dice = { 0, 0, 0, 0, 0, 0, 0, 0 };
	scanf("%d %d %d %d %d", &n, &m, &dice.x, &dice.y, &k);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			scanf("%d", &map[i][j]);
	while (k--)
	{
		int order;
		scanf("%d", &order);

		if (!RollDice(order)) continue; // 범위를 벗어난다면, 무시.
		if (map[dice.x][dice.y] != 0)	// 지도와 주사위 아래 값 갱신.
		{
			dice.d = map[dice.x][dice.y];
			map[dice.x][dice.y] = 0;
		}
		else map[dice.x][dice.y] = dice.d;

		printf("%d\n", dice.u);
	}
	return 0;
}