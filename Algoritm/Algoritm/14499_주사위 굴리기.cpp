#include <stdio.h>
#include <algorithm>
using namespace std;

const int MAX = 21;

int n, m, x, y, k, dice[7], map[MAX][MAX]; // 행, 열, 인덱스 0 부터.
int direction[5][2] = { {0, 0}, {0, 1}, {0, -1}, {-1, 0}, {1, 0} }; // 1 부터.
struct DiceStatus { int back, top, front, bottom, left, right; };
DiceStatus diceStatus;

void initDice()
{
	diceStatus.back = 2;
	diceStatus.top = 1;
	diceStatus.front = 5;
	diceStatus.bottom = 6;
	diceStatus.left = 4;
	diceStatus.right = 3;
}

void rollDice(int dir)
{
	if (dir == 1) // 동
	{
		int bottom = diceStatus.bottom;
		int top = diceStatus.top;
		diceStatus.bottom = diceStatus.right;
		diceStatus.top = diceStatus.left;
		diceStatus.right = top;
		diceStatus.left = bottom;
	}
	else if (dir == 2) // 서
	{
		int bottom = diceStatus.bottom;
		int top = diceStatus.top;
		diceStatus.bottom = diceStatus.left;
		diceStatus.top = diceStatus.right;
		diceStatus.right = bottom;
		diceStatus.left = top;
	}
	else if (dir == 3) // 남
	{
		int bottom = diceStatus.bottom;
		diceStatus.bottom = diceStatus.front;
		diceStatus.front = diceStatus.top;
		diceStatus.top = diceStatus.back;
		diceStatus.back = bottom;
	}
	else // 북
	{
		int back = diceStatus.back;
		diceStatus.back = diceStatus.top;
		diceStatus.top = diceStatus.front;
		diceStatus.front = diceStatus.bottom;
		diceStatus.bottom = back;
	}
}

int main()
{
	scanf("%d %d %d %d %d", &n, &m, &x, &y, &k);
	for (int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			scanf("%d", &map[i][j]);
	
	initDice();
	for (int kk = 0; kk < k; kk++)
	{
		int dir;
		scanf("%d", &dir);
		x += direction[dir][0]; // 주사위 밑면 좌표.
 		y += direction[dir][1];
		if (x < 0 || y < 0 || x >= n || y >= m) // 바깥으로 넘어가면,
		{
			x -= direction[dir][0]; // 원상 복귀.
			y -= direction[dir][1];
			continue; // 다음 명령 수행.
		}

		rollDice(dir); // dir로 굴린 후의 주사위 상태.
		if (map[x][y]) // 지도에 값이 있으면,
		{
			dice[diceStatus.bottom] = map[x][y]; // 복사.
			map[x][y] = 0; // 복사 후, 0 으로 세팅.
		}
		else map[x][y] = dice[diceStatus.bottom]; // 없으면, 주사위 값 복사.
		printf("%d\n", dice[diceStatus.top]);
	}

	return 0;
}