#include <stdio.h>
#include <string.h>
#include <queue>
using namespace std;

const int MAX = 101;

int n, m, map[MAX][MAX], visited[MAX][MAX];
int dir[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

void showMap()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			printf("%d ", map[i][j]);
		printf("\n");
	}
	printf("\n");
}

void melting()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			if (map[i][j] == 2) map[i][j] = 0;	
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
		if (!map[next_r][next_c]) { flag = 1;  break; }
	}

	if (flag) return true;
	else	  return false;
}

/* bfs �� ���� ġ���� ���� ��ȯ */
int bfs(int r, int c)
{
	queue<pair<int, int>> q;
	q.push(pair<int, int>(r, c));
	visited[r][c] = 1;
	map[r][c] = 2; // ������ 2�� �ٲ� (0���� �ٲٸ� ��ħ)

	int curMeltCnt = 1; // ���� ���� ġ�� ����
	while (!q.empty())
	{
		pair<int, int> cur = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) // ġ�� ã��
		{
			int next_r = cur.first + dir[i][0];
			int next_c = cur.second + dir[i][1];
			if (next_r < 1 || next_c < 1 || next_r >= n - 1 || next_c >= m - 1) continue;
			if (!map[next_r][next_c] || visited[next_r][next_c]) continue;

			/* ġ�� ó�� �߰� */

			if (chkMelt(next_r, next_c)) // ��� ������
			{
				curMeltCnt++; // ���� ġ�� ī����
				map[next_r][next_c] = 2; // ���� ġ��� 2�� ǥ��
			}

			visited[next_r][next_c] = 1;
			q.push(pair<int, int>(next_r, next_c));
		}
	}

	//printf("return: %d\n", curMeltCnt); showMap();
	return curMeltCnt;
}

int main()
{
	scanf("%d %d", &n, &m);

	int cheeseCnt = 0; // ��ü ġ�� ����
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			scanf("%d", &map[i][j]);
			if (map[i][j]) cheeseCnt++;
		}
	}

	int meltTime = 0; // ���� ��µ� �ɸ� �ð�
	while (cheeseCnt)
	{
		int meltCnt = 0; // �� �ð��� ���� ����
		for (int i = 1; i < n - 1; i++)
		{
			for (int j = 1; j < m - 1; j++)
			{
				if (map[i][j] && !visited[i][j])
					meltCnt += bfs(i, j);
			}
		}
		meltTime++;
		
		if (meltCnt == cheeseCnt)
		{
			printf("%d\n%d\n", meltTime, meltCnt);
			break;
		}

		melting(); //showMap();
		cheeseCnt -= meltCnt;
		for (int i = 0; i < n; i++)
			memset(&visited[i], 0, sizeof(int) * m);
	}

	return 0;
}