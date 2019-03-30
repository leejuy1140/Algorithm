#include <stdio.h>
#include <string.h>

const int MAP_MAX = 505;
const int SPIN_MAX = 10;

int x, y, score; // 현재 위치 (열, 행)
int n, m, map[MAP_MAX][MAP_MAX]; // 행, 열
int k, spindleIdx, spindle[SPIN_MAX];
int dir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} }; // x, y (EWSN)

/* 회전판을 명령에 따라 돌린 후, 로봇을 이동시킬 칸 반환 */
int turnSpindle(int spinDir, int spinCnt)
{
	if (spinDir == 1) // 시계방향
	{
		for (int i = 0; i < spinCnt; i++)
		{
			spindleIdx--;
			if (spindleIdx < 1) spindleIdx = k;
		}
	}
	else
	{
		for (int i = 0; i < spinCnt; i++)
		{
			spindleIdx++;
			if (spindleIdx > k) spindleIdx = 1;
		}
	}
	return spindle[spindleIdx];
}

void moveRobot(int dirIdx, int moveCnt)
{
	if (!moveCnt) return;

	int nx = x + dir[dirIdx][0];
	int ny = y + dir[dirIdx][1];
	if (nx < 1 || nx > m || ny < 1 || ny > n) return;
	if (map[ny][nx] == -1) return;

	x = nx;
	y = ny;
	score += map[y][x];
	map[y][x] = 0;
	return moveRobot(dirIdx, moveCnt - 1);
}

int main()
{
	int t;
	scanf("%d", &t);
	for (int tt = 1; tt <= t; tt++)
	{
		scanf("%d %d %d %d", &m, &n, &x, &y);
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				scanf("%d", &map[i][j]);
		scanf("%d", &k);
		for (int i = 1; i <= k; i++)
			scanf("%d", &spindle[i]);

		score = map[y][x];
		map[y][x] = 0;
		spindleIdx = 1;

		int l;
		scanf("%d", &l);
		for (int i = 1; i <= l; i++)
		{
			char moveDir;
			int spinDir, spinCnt;
			getchar();
			scanf("%c %d %d", &moveDir, &spinDir, &spinCnt);

			int dirIdx, moveCnt;
			if (moveDir == 'E') dirIdx = 0;
			else if (moveDir == 'W') dirIdx = 1;
			else if (moveDir == 'S') dirIdx = 2;
			else dirIdx = 3;

			moveCnt = turnSpindle(spinDir, spinCnt);
			moveRobot(dirIdx, moveCnt);
		}
		printf("#%d %d %d %d\n", tt, score, x, y);
	}

	return 0;
}