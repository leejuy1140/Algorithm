#include <stdio.h>
#include <queue>
using namespace std;

const int MAX = 105;
const int APPLE = 1;
const int SNAKE = 2;

queue<pair<int, int>> body;
queue<pair<int, char>> change;
int n, board[MAX][MAX], time = -1;
int direction[4][2] = { {0, 1},  {0, -1}, {-1, 0}, {1, 0} }; // rlud

/*
1. 뱀은 몸길이를 늘려 머리를 다음칸에 위치시킨다.
2. 이동한 칸에 사과가 있다면,
   그 칸에 있던 사과가 없어지고 꼬리는 움직이지 않는다.
3. 이동한 칸에 사과가 없다면,
   몸길이를 줄여서 꼬리가 위치한 칸을 비워준다.
   즉, 몸길이는 변하지 않는다.
4. 벽 또는 자기자신의 몸과 부딪히면 게임이 끝난다.

왼쪽('L'), 오른쪽('D')
*/

void showBoard()
{
	printf("\n[%d]\n", time);
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
			printf("%d ", board[i][j]);
		printf("\n");
	}
}

int changeDir(int curDir)
{
	if (curDir == 0) // 현재 오른쪽
	{
		if (change.front().second == 'D') return 3;
		else							  return 2;
	}
	if (curDir == 1) // 현재 왼쪽
	{
		if (change.front().second == 'D') return 2;
		else							  return 3;
	}
	if (curDir == 2) // 현재 위쪽
	{
		if (change.front().second == 'D') return 0;
		else							  return 1;
	}
	if (curDir == 3) // 현재 아래쪽
	{
		if (change.front().second == 'D') return 1;
		else							  return 0;
	}
}

void dummyGame(int r, int c, int dir)
{
	/* 1. 현재 위치가 사과가 아니면, 꼬리 자름. */
	body.push(make_pair(r, c));
	if (time != -1 && board[r][c] != APPLE)
	{
		pair<int, int> tail = body.front();
		body.pop();
		board[tail.first][tail.second] = 0;
	}
	board[r][c] = SNAKE;
	
	/* 2. 시간 경과 체크. 방향 전환할 시간이면, 전환. */
	time++;
	if (!change.empty())
	{
		if (change.front().first == time)
		{
			dir = changeDir(dir);
			change.pop();
		}
	}
	//showBoard();

	/* 3. 다음 위치 찾기. */
	int nr = r + direction[dir][0];
	int nc = c + direction[dir][1];
	if (nr < 1 || nc < 1 || nr > n || nc > n) return; // 벽 -> 종료.
	if (board[nr][nc] == SNAKE)				  return; // 몸 -> 종료.
	return dummyGame(nr, nc, dir);
}

int main()
{
	int k, l;
	scanf("%d\n%d", &n, &k);
	for (int i = 0; i < k; i++)
	{
		int r, c;
		scanf("%d %d", &r, &c);
		board[r][c] = APPLE;
	}
	scanf("%d", &l);
	for (int i = 0; i < l; i++)
	{
		char dir; int sec;
		scanf("%d", &sec);
		getchar(); scanf("%c", &dir);
		change.push(make_pair(sec, dir));
	}

	dummyGame(1, 1, 0);
	printf("%d\n", time + 1);

	return 0;
}