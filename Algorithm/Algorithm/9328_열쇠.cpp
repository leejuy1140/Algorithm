#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

const int MAX = 105;

int n, m, key;
char map[MAX][MAX];
bool visited[MAX][MAX];
int dir[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

// 1. map의 밖을 '.'으로 패딩. (자유롭게 나갈 수 있도록)
// 2. bfs를 돌리며, map을 탐색.
// 3. 새로운 열쇠를 못 찾을 때까지, 2번 반복.

bool isDoor(char a)
{
	return a >= 'A' && a <= 'Z';
}

bool isKey(char a)
{
	return a >= 'a' && a <= 'z';
}

int FindPaper()
{
	int paper = 0;
	bool keyUpdate = true;
	queue<pair<int, int>> q;

	while (keyUpdate) // 새로운 열쇠를 찾을 때까지, bfs 반복.
	{
		q.push(make_pair(0, 0));
		visited[0][0] = true;
		keyUpdate = false;

		while (!q.empty())
		{
			int r = q.front().first;
			int c = q.front().second;
			q.pop();

			if (isKey(map[r][c])) // 1. 열쇠면, 열쇠 추가.
			{
				int move = map[r][c] - 'a';
				key |= 1 << move;
				keyUpdate = true;
				map[r][c] = '.';
			}
			if (isDoor(map[r][c])) // 2. 문이면, 열쇠 확인.
			{
				int move = map[r][c] - 'A';
				if (key & (1 << move)) map[r][c] = '.'; // 있으면, 문 열기.
				else				   continue;		// 없으면, 못 지나감.
			}
			if (map[r][c] == '$') // 3. 문서면, 수집.
			{
				paper++;
				map[r][c] = '.';
			}

			for (int i = 0; i < 4; i++)
			{
				int nr = r + dir[i][0];
				int nc = c + dir[i][1];
				if (nr < 0 || nc < 0 || nr > n + 1 || nc > m + 1) continue;
				if (visited[nr][nc] || map[nr][nc] == '*') continue;

				q.push(make_pair(nr, nc));
				visited[nr][nc] = true;
			}
		}
		memset(visited, false, sizeof(visited));
	}

	return paper;
}

int main()
{
	int tc;
	scanf("%d", &tc);
	while (tc--)
	{
		char tmp[30];
		scanf("%d %d", &n, &m);
		for (int i = 1; i <= n; i++)
		{
			getchar();
			for (int j = 1; j <= m; j++)
				scanf("%1c", &map[i][j]);
		}
		getchar();
		scanf("%s", tmp);
		if (tmp[0] != '0')
		{
			for (int i = 0; i < strlen(tmp); i++)
			{
				int move = tmp[i] - 'a';
				key |= (1 << move);
			}
		}

		// 상근이가 자유롭게 나갈 수 있도록, map 밖을 '.'으로 패딩.
		for (int i = 0; i <= n + 1; i++)
		{
			map[i][0] = '.';
			map[i][m + 1] = '.';
		}
		for (int i = 0; i <= m + 1; i++)
		{
			map[0][i] = '.';
			map[n + 1][i] = '.';
		}

		// map을 돌아다니며, 문서 수집.
		int answer = FindPaper();
		printf("%d\n", answer);

		key = 0;
		memset(visited, false, sizeof(visited));
	}
	return 0;
}