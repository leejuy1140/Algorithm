#include <iostream>
#include <queue>
using namespace std;

const int MAX = 51;
const int MACHINE = -1;

int up, down; // ����û������ �� ��.
int R, C, T, map[MAX][MAX];
int dr[4] = { 0, 0, -1, 1 };
int dc[4] = { -1, 1, 0, 0 };
struct Dust { int r, c, dust; };

void SpreadDust()
{
	// ������ �ִ� �� ���� ť�� �ְ�
	queue<Dust> q;
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)
			if (map[i][j] > 0) q.push({ i, j, map[i][j] });

	// 4�������� Ȯ��.
	while (!q.empty())
	{
		Dust cur = q.front();
		q.pop();

		int add = cur.dust / 5;
		for (int i = 0; i < 4; i++)
		{
			int nr = cur.r + dr[i];
			int nc = cur.c + dc[i];
			if (nr < 0 || nc < 0 || nr >= R || nc >= C) continue;
			if (map[nr][nc] == MACHINE) continue;

			map[nr][nc] += add;
			map[cur.r][cur.c] -= add;
		}
	}
}

void ClearUp()
{
	int r = up;
	int c = 1;
	int dir = 0;
	int tmp = 0;
	while (map[r][c] != MACHINE)
	{
		int cur = map[r][c];
		map[r][c] = tmp;
		tmp = cur;

		if (dir == 0) // ����������
		{
			c++;
			if (c == C) // ���̸�, ����
			{
				r--;
				c = C - 1;
				dir++;
			}
		}
		else if (dir == 1) // ����
		{
			r--;
			if (r < 0) // ���̸�, ��������
			{
				c--;
				r = 0;
				dir++;
			}
		}
		else if (dir == 2) // �������� 
		{
			c--;
			if (c < 0) // ���̸�, �Ʒ���
			{
				r++;
				c = 0;
				dir++;
			}
		}
		else r++; // �Ʒ���
	}
}

void ClearDown()
{
	int r = down;
	int c = 1;
	int dir = 0;
	int tmp = 0;
	while (map[r][c] != MACHINE)
	{
		int cur = map[r][c];
		map[r][c] = tmp;
		tmp = cur;

		if (dir == 0) // ����������
		{
			c++;
			if (c == C) // ���̸�, �Ʒ���
			{
				r++;
				c = C - 1;
				dir++;
			}
		}
		else if (dir == 1) // �Ʒ�
		{
			r++;
			if (r == R) // ���̸�, ��������
			{
				c--;
				r = R - 1;
				dir++;
			}
		}
		else if (dir == 2) // �������� 
		{
			c--;
			if (c < 0) // ���̸�, ����
			{
				r--;
				c = 0;
				dir++;
			}
		}
		else r--; // �Ʒ���
	}
}

int main()
{
	scanf("%d %d %d", &R, &C, &T);
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			scanf("%d", &map[i][j]);
			if (map[i][j] == MACHINE)
			{
				if (!up) up = i;
				else	 down = i;
			}
		}
	}

	while (T--)
	{
		SpreadDust();
		ClearUp();
		ClearDown();
	}

	int answer = 0;
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)
			if(map[i][j] > 0) answer += map[i][j];
	printf("%d", answer);

	return 0;
}