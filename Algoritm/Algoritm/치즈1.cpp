#include <stdio.h>
#include <string.h>
#include <queue>
using namespace std;

const int MAX = 105;
enum { WHOLE = -1, AIR, CHEESE, MELTED };

int n, m, map[MAX][MAX], visited[MAX][MAX];
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
	visited[r][c] = 1;
	if (r && c) map[r][c] = WHOLE;

	while (!q.empty())
	{
		pair<int, int> cur = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) // 구멍 찾기
		{
			int next_r = cur.first + dir[i][0];
			int next_c = cur.second + dir[i][1];
			if (next_r < 0 || next_c < 0 || next_r >= n || next_c >= m) continue;
			
			if (map[next_r][next_c] == AIR && !visited[next_r][next_c])
			{
				q.push(pair<int, int>(next_r, next_c));
				visited[next_r][next_c] = 1;
				if (r && c) map[next_r][next_c] = WHOLE;
			}
		}
	}
}

/* 공기에 닿아서 녹으면 true 반환 */
bool chkMelt(int r, int c)
{
	int flag = 0;
	for (int i = 0; i < 4; i++)
	{
		int next_r = r + dir[i][0];
		int next_c = c + dir[i][1];
		if (next_r < 0 || next_c < 0 || next_r >= n || next_c >= m) continue;
		if (map[next_r][next_c] == AIR) { flag = 1; break; }
	}
	if (flag) return true;
	else	  return false;
}

/* 녹은 치즈의 개수 반환 */
int findCheese(int r, int c)
{
	int curMeltCnt = 0; // 현재 녹은 치즈 개수
	if (chkMelt(r, c)) // 녹아 없어짐
	{
		curMeltCnt++; // 녹은 치즈 카운팅
		map[r][c] = MELTED; // 녹은 치즈 표시
	}

	queue<pair<int, int>> q;
	q.push(pair<int, int>(r, c));
	visited[r][c] = 1;

	while (!q.empty())
	{
		pair<int, int> cur = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) // 치즈 찾기
		{
			int next_r = cur.first + dir[i][0];
			int next_c = cur.second + dir[i][1];
			if (next_r < 1 || next_c < 1 || next_r >= n - 1 || next_c >= m - 1) continue;
			
			if (map[next_r][next_c] == CHEESE && !visited[next_r][next_c])
			{
				if (chkMelt(next_r, next_c))
				{
					curMeltCnt++;
					map[next_r][next_c] = MELTED;
				}
				visited[next_r][next_c] = 1;
				q.push(pair<int, int>(next_r, next_c));
			}
		}
	}
	return curMeltCnt;
}

int main()
{
	int cheeseCnt = 0; // 전체 치즈 개수
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			scanf("%d", &map[i][j]);
			if (map[i][j]) cheeseCnt++;
		}
	}

	int meltCnt = 0; // 한 시간에 녹은 치즈 개수
	int meltTime = 0; // 전부 녹는데 걸린 시간

	while (cheeseCnt)
	{
		for (int i = 0; i < n; i++)
			memset(&visited[i], 0, sizeof(int) * m);

		/* 치즈 구멍 체크.
		   (0,0)에서 시작되지 않은 구멍(내부 구멍)들은 전부 음수 표시 ! */
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				if (map[i][j] == AIR && !visited[i][j]) chkWhole(i, j);

		for (int i = 0; i < n; i++)
			memset(&visited[i], 0, sizeof(int) * m);

		/* 녹은 치즈 체크 및 한 시간 동안 녹은 치즈 개수 반환 */
		meltCnt = 0;
		for (int i = 1; i < n - 1; i++)
			for (int j = 1; j < m - 1; j++)
				if (map[i][j] == CHEESE && !visited[i][j]) meltCnt += findCheese(i, j);

		melting(); // 녹은 치즈 및 구멍 없앰
		meltTime++; // 시간 경과 체크
		cheeseCnt -= meltCnt; // 현재 남은 치즈 개수 갱신
	}
	printf("%d\n%d\n", meltTime, meltCnt);

	return 0;
}