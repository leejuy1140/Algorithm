#include <stdio.h>
#include <algorithm>
using namespace std;

const int MAX = 21;

int n, m, x, y, k, dice[7], map[MAX][MAX]; // ��, ��, �ε��� 0 ����.
int direction[5][2] = { {0, 0}, {0, 1}, {0, -1}, {-1, 0}, {1, 0} }; // 1 ����.
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
	if (dir == 1) // ��
	{
		int bottom = diceStatus.bottom;
		int top = diceStatus.top;
		diceStatus.bottom = diceStatus.right;
		diceStatus.top = diceStatus.left;
		diceStatus.right = top;
		diceStatus.left = bottom;
	}
	else if (dir == 2) // ��
	{
		int bottom = diceStatus.bottom;
		int top = diceStatus.top;
		diceStatus.bottom = diceStatus.left;
		diceStatus.top = diceStatus.right;
		diceStatus.right = bottom;
		diceStatus.left = top;
	}
	else if (dir == 3) // ��
	{
		int bottom = diceStatus.bottom;
		diceStatus.bottom = diceStatus.front;
		diceStatus.front = diceStatus.top;
		diceStatus.top = diceStatus.back;
		diceStatus.back = bottom;
	}
	else // ��
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
		x += direction[dir][0]; // �ֻ��� �ظ� ��ǥ.
 		y += direction[dir][1];
		if (x < 0 || y < 0 || x >= n || y >= m) // �ٱ����� �Ѿ��,
		{
			x -= direction[dir][0]; // ���� ����.
			y -= direction[dir][1];
			continue; // ���� ��� ����.
		}

		rollDice(dir); // dir�� ���� ���� �ֻ��� ����.
		if (map[x][y]) // ������ ���� ������,
		{
			dice[diceStatus.bottom] = map[x][y]; // ����.
			map[x][y] = 0; // ���� ��, 0 ���� ����.
		}
		else map[x][y] = dice[diceStatus.bottom]; // ������, �ֻ��� �� ����.
		printf("%d\n", dice[diceStatus.top]);
	}

	return 0;
}