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

/* (r, c)�� ���ӵ� ���� ���� �ѿ� ���� ��ȯ. */
bool findPuyo(int r, int c, char color)
{
	vector<pair<int, int>> pop; // ���ӵ� �ѿ��� ��ġ.

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

	if (pop.size() >= 4) // �Ͷ߸� �ѿ䰡 4�� �̻��̸� �Ͷ߸�.
	{
		for (int i = 0; i < pop.size(); i++)
			map[pop[i].first][pop[i].second] = '.';
		return true;
	}
	return false;
}

/* �ѿ�� �Ʒ��� ������. */
void downPuyo()
{
	for (int i = 0; i < C_MAX; i++)			 // ��� ���� ���Ͽ�
	{
		for (int j = R_MAX - 1; j >= 0; j--) // �� ���� �� �Ʒ�����
		{
			if (map[j][i] == '.')			 // ��ĭ�̸�,
			{
				for (int k = j - 1; k >= 0; k--) // ��ĭ ������
				{
					if (map[k][i] != '.')		 // ���� ã�Ƽ� ��ȯ.
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

	int answer = 0; // ���� Ƚ��.
	while (1)
	{
		bool flag = false; // �ѿ䰡 ��������, true
		memset(visited, false, sizeof(visited));

		// 1. ���� �� �ִ� �ѿ� ã�Ƽ� �Ͷ߸���. ('.'���� �����ϱ�)
		for (int i = R_MAX - 1; i >= 0; i--)
		{
			for (int j = 0; j < C_MAX; j++)
			{
				if (map[i][j] != '.' && !visited[i][j]) // ��������, ture.
					if (findPuyo(i, j, map[i][j])) flag = true;
			}
		}
		if (!flag) break; // ���̻� ���� �ѿ䰡 ������ Ż��.

		// 2. �ѿ� �ϰ���Ű��.
		answer++;
		downPuyo();
	}
	cout << answer;

	return 0;
}