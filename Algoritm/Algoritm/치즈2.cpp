#include <stdio.h>
#include <string.h>
#include <queue>
using namespace std;

const int MAX = 105;
enum { WHOLE = -1, AIR, CHEESE, MELTED };

int n, m, map[MAX][MAX];
bool visitedWhole[MAX][MAX], visitedCheese[MAX][MAX];
int dir[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

void melting()
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (map[i][j] == MELTED || map[i][j] == WHOLE) map[i][j] = AIR;
}

void chkWhole(int r, int c)
{
	queue<pair<int, int>> q;
	q.push(pair<int, int>(r, c));
	visitedWhole[r][c] = 1;
	if (r && c) map[r][c] = WHOLE;

	while (!q.empty())
	{
		pair<int, int> cur = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) // ���� ã��
		{
			int next_r = cur.first + dir[i][0];
			int next_c = cur.second + dir[i][1];
			if (next_r < 0 || next_c < 0 || next_r >= n || next_c >= m) continue;

			if (map[next_r][next_c] == AIR && !visitedWhole[next_r][next_c])
			{
				q.push(pair<int, int>(next_r, next_c));
				visitedWhole[next_r][next_c] = 1;
				if (r && c) map[next_r][next_c] = WHOLE;
			}
		}
	}
}

/* ���⿡ ��Ƽ� ������ true ��ȯ */
bool chkMelt(int r, int c)
{
	int flag = 0;
	for (int i = 0; i < 4; i++)
	{
		int next_r = r + dir[i][0];
		int next_c = c + dir[i][1];
		if (next_r < 0 || next_c < 0 || next_r >= n || next_c >= m) continue;
		if (map[next_r][next_c] == AIR) { flag++; }
	}
	if (flag >= 2) return true;
	else	       return false;
}

/* ���� ġ���� ���� ��ȯ */
int findCheese(int r, int c)
{
	int curMeltCnt = 0; // ���� ���� ġ�� ����
	if (chkMelt(r, c)) // ��� ������
	{
		curMeltCnt++; // ���� ġ�� ī����
		map[r][c] = MELTED; // ���� ġ�� ǥ��
	}

	queue<pair<int, int>> q;
	q.push(pair<int, int>(r, c));
	visitedCheese[r][c] = 1;

	while (!q.empty())
	{
		pair<int, int> cur = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) // ġ�� ã��
		{
			int next_r = cur.first + dir[i][0];
			int next_c = cur.second + dir[i][1];
			if (next_r < 1 || next_c < 1 || next_r >= n - 1 || next_c >= m - 1) continue;

			if (map[next_r][next_c] == CHEESE && !visitedCheese[next_r][next_c])
			{
				if (chkMelt(next_r, next_c))
				{
					curMeltCnt++;
					map[next_r][next_c] = MELTED;
				}
				visitedCheese[next_r][next_c] = 1;
				q.push(pair<int, int>(next_r, next_c));
			}
		}
	}
	return curMeltCnt;
}

int main()
{
	int cheeseCnt = 0; // ��ü ġ�� ����
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			scanf("%d", &map[i][j]);
			if (map[i][j]) cheeseCnt++;
		}
	}

	int meltTime = 0;
	while (cheeseCnt)
	{
		/* ġ�� ���� üũ.
		   (0,0)���� ���۵��� ���� ����(���� ����)���� ���� ���� ǥ�� ! */
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				if (map[i][j] == AIR && !visitedWhole[i][j]) chkWhole(i, j);

		/* ���� ġ�� üũ �� �� �ð� ���� ���� ġ�� ���� ��ȯ */
		int meltCnt = 0;
		for (int i = 1; i < n - 1; i++)
			for (int j = 1; j < m - 1; j++)
				if (map[i][j] == CHEESE && !visitedCheese[i][j]) meltCnt += findCheese(i, j);

		melting(); // ���� ġ�� �� ���� ����
		meltTime++; // �ð� ��� üũ
		cheeseCnt -= meltCnt; // ���� ���� ġ�� ���� ����
		for (int i = 0; i < n; i++) memset(&visitedWhole[i], 0, m);
		for (int i = 0; i < n; i++) memset(&visitedCheese[i], 0, m);
	}
	printf("%d\n", meltTime);

	return 0;
}