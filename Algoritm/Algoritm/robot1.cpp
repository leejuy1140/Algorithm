#include <stdio.h>
#include <string.h>

const int MAP_MAX = 505;
const int SPIN_MAX = 8;

int n, m, x, y, k, l;
int moveDir, spinDir, spinCnt, spinIdx, score;
int spindle[SPIN_MAX], map[MAP_MAX][MAP_MAX];
int direction[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} }; // 동서남북

void initInput()
{
	scanf("%d %d %d %d", &n, &m, &x, &y);
	x--; y--;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			scanf("%d", &map[i][j]);
	}
	scanf("%d", &k);
	for (int i = 0; i < k; i++)
		scanf("%d", &spindle[i]);
	spinIdx = 0;
	score = 0;
	return;
}

int getMoveDirection()
{
	if (moveDir == 'E') return 0;
	if (moveDir == 'W') return 1;
	if (moveDir == 'S') return 2;
	if (moveDir == 'N') return 3;
}

int spin()
{
	if (spinDir == 1) // 시계 방향 (-1)
	{
		for (int i = 0; i < spinCnt; i++)
		{
			spinIdx--;
			if (spinIdx == -1) spinIdx = k - 1;
		}
	}
	else // 반시계 방향 (+1)
	{
		for (int i = 0; i < spinCnt; i++)
			spinIdx = (spinIdx + 1) % k;
	}
	return spindle[spinIdx];
}

void move(int cur_x, int cur_y, int moveCnt)
{
	if (moveCnt == 0) return;
	if (cur_x < 0 || cur_y < 0 || cur_x >= n || cur_y >= m) return;
	if (map[cur_y][cur_x] == -1) return;

	score += map[cur_y][cur_x];
	map[cur_y][cur_x] = 0;
	x = cur_x; y = cur_y;

	int new_x = cur_x + direction[moveDir][0];
	int new_y = cur_y + direction[moveDir][1];
	move(new_x, new_y, moveCnt - 1);
}

int main()
{
	int t;
	scanf("%d", &t);
	for(int k = 1; k <= t; k++)
	{
		initInput();
		scanf("%d", &l);
		for (int i = 0; i < l; i++)
		{
			getchar(); scanf("%c", &moveDir);
			scanf("%d %d", &spinDir, &spinCnt);
			
			int moveCnt = spin();
			moveDir = getMoveDirection();
			move(x, y, moveCnt + 1);
		}
		printf("#%d %d %d %d\n", k, score, x + 1, y + 1);
	}

	return 0;
}