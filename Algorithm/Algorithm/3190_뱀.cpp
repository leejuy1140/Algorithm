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
1. ���� �����̸� �÷� �Ӹ��� ����ĭ�� ��ġ��Ų��.
2. �̵��� ĭ�� ����� �ִٸ�,
   �� ĭ�� �ִ� ����� �������� ������ �������� �ʴ´�.
3. �̵��� ĭ�� ����� ���ٸ�,
   �����̸� �ٿ��� ������ ��ġ�� ĭ�� ����ش�.
   ��, �����̴� ������ �ʴ´�.
4. �� �Ǵ� �ڱ��ڽ��� ���� �ε����� ������ ������.

����('L'), ������('D')
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
	if (curDir == 0) // ���� ������
	{
		if (change.front().second == 'D') return 3;
		else							  return 2;
	}
	if (curDir == 1) // ���� ����
	{
		if (change.front().second == 'D') return 2;
		else							  return 3;
	}
	if (curDir == 2) // ���� ����
	{
		if (change.front().second == 'D') return 0;
		else							  return 1;
	}
	if (curDir == 3) // ���� �Ʒ���
	{
		if (change.front().second == 'D') return 1;
		else							  return 0;
	}
}

void dummyGame(int r, int c, int dir)
{
	/* 1. ���� ��ġ�� ����� �ƴϸ�, ���� �ڸ�. */
	body.push(make_pair(r, c));
	if (time != -1 && board[r][c] != APPLE)
	{
		pair<int, int> tail = body.front();
		body.pop();
		board[tail.first][tail.second] = 0;
	}
	board[r][c] = SNAKE;
	
	/* 2. �ð� ��� üũ. ���� ��ȯ�� �ð��̸�, ��ȯ. */
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

	/* 3. ���� ��ġ ã��. */
	int nr = r + direction[dir][0];
	int nc = c + direction[dir][1];
	if (nr < 1 || nc < 1 || nr > n || nc > n) return; // �� -> ����.
	if (board[nr][nc] == SNAKE)				  return; // �� -> ����.
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