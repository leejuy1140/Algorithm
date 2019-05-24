#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

const int R_MAX = 12;
const int C_MAX = 6;

char map[R_MAX][C_MAX];
bool visited[R_MAX][C_MAX];
int dr[4] = { 0, 0, 1, -1 };
int dc[4] = { 1, -1, 0, 0 };

/* (r, c)와 연속된 같은 색의 뿌요 개수 반환. */
bool findPuyo(int r, int c, char color)
{
	vector<pair<int, int>> pop; // 연속된 뿌요의 위치.

	queue<pair<int, int>> q;
	q.push({ r, c });
	visited[r][c] = true;
	pop.push_back({ r, c });

	while (!q.empty())
	{
		pair<int, int> cur = q.front();
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			int nr = cur.first + dr[i];
			int nc = cur.second + dc[i];
			if (nr < 0 || nr >= R_MAX || nc < 0 || nc >= C_MAX) continue;
			if (visited[nr][nc] || map[nr][nc] != color) continue;

			q.push({ nr, nc });
			visited[nr][nc] = true;
			pop.push_back({ nr, nc });
		}
	}

	if (pop.size() >= 4) // 터뜨릴 뿌요가 4개 이상이면 터뜨림.
	{
		for (int i = 0; i < pop.size(); i++)
			map[pop[i].first][pop[i].second] = '.';
		return true;
	}
	return false;
}

/* 뿌요들 아래로 내리기. */
void downPuyo()
{
	for (int i = 0; i < C_MAX; i++)			 // 모든 열에 대하여
	{
		for (int j = R_MAX - 1; j >= 0; j--) // 각 행의 맨 아래부터
		{
			if (map[j][i] == '.')			 // 빈칸이면,
			{
				for (int k = j - 1; k >= 0; k--) // 빈칸 위부터
				{
					if (map[k][i] != '.')		 // 블럭을 찾아서 교환.
					{
						map[j][i] = map[k][i];
						map[k][i] = '.';
						break;
					}
				}
			}
		}
	}
}

int main()
{
	for (int i = 0; i < R_MAX; i++)
		for (int j = 0; j < C_MAX; j++)
			cin >> map[i][j];

	int answer = 0; // 연쇄 횟수.
	while (1)
	{
		bool flag = false; // 뿌요가 터졌으면, true
		memset(visited, false, sizeof(visited));

		// 1. 터질 수 있는 뿌요 찾아서 터뜨리기. ('.'으로 변경하기)
		for (int i = R_MAX - 1; i >= 0; i--)
		{
			for (int j = 0; j < C_MAX; j++)
			{
				if (map[i][j] != '.' && !visited[i][j]) // 터졌으면, ture.
					if (findPuyo(i, j, map[i][j])) flag = true;
			}
		}
		if (!flag) break; // 더이상 터질 뿌요가 없으니 탈출.

		// 2. 뿌요 하강시키기.
		answer++;
		downPuyo();
	}
	cout << answer;

	return 0;
}