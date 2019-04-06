#include <iostream>
#include <queue>
using namespace std;

const int MAX = 51;

int room[MAX * MAX];  // �ε���: �� ��ȣ, ��: ũ��.
int castle[MAX][MAX]; // �渶�� ���ڷ� üũ.
int n, m, map[MAX][MAX];
int dir[4][2] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0} }; // ���ϵ���(1248)

/* ���� ���� üũ�ϰ� ���� ũ�� ��ȯ. */
int CheckRoom(int r, int c, int num)
{
	queue<pair<int, int>> q;
	q.push(make_pair(r, c));
	castle[r][c] = num;

	int area = 1;
	while (!q.empty())
	{
		int rr = q.front().first;
		int cc = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			if (map[rr][cc] & (1 << i)) continue; // ���̸� �н�.

			int nr = rr + dir[i][0];
			int nc = cc + dir[i][1];
			if (nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
			if (castle[nr][nc]) continue;

			q.push(make_pair(nr, nc));
			castle[nr][nc] = num;
			area++;
		}
	}
	return area;
}

int main()
{
	scanf("%d %d", &m, &n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			scanf("%d", &map[i][j]);
	
	// bfs�� ����, ���� ������ ���� ū ���� ũ�� ã��.
	int num = 0;	 // ���� ����.
	int maxArea = 0; // ���� ū ���� ũ��.
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (!castle[i][j])
			{
				num++;
				room[num] = CheckRoom(i, j, num);
				maxArea = maxArea > room[num] ? maxArea : room[num];
			}
		}
	}

	// ������ �� ���� ũ�⸦ ���� �� �� ���� ū �� ã��.
	int maxMergeArea = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (castle[i][j] != castle[i][j + 1]) // �¿� ����.
			{
				int curArea = room[castle[i][j]] + room[castle[i][j + 1]];
				maxMergeArea = maxMergeArea > curArea ? maxMergeArea : curArea;
			}
			if (castle[i][j] != castle[i + 1][j]) // ���� ����.
			{
				int curArea = room[castle[i][j]] + room[castle[i + 1][j]];
				maxMergeArea = maxMergeArea > curArea ? maxMergeArea : curArea;
			}
		}
	}
	printf("%d\n%d\n%d", num, maxArea, maxMergeArea);

	return 0;
}