#include <stdio.h>
#include <string.h> // �迭 �ʱ�ȭ.
#include <queue>	// bfs
using namespace std;

const int MAX = 51;

queue<pair<int, int>> q;
int together[MAX][MAX];	   // ������ ������� ���ڷ� ǥ��.
bool visited[MAX][MAX];	   // bfs �ߺ� ����.
int population[MAX * MAX]; // �ش� ���ձ��� �α��̵��� �α��� ����.

int n, L, R, map[MAX][MAX];
int dir[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

int inline MyAbs(int num) {
	return num < 0 ? -num : num;
}

/* (r, c) ���󿡼� �����Ͽ�, ������ ���� num���� ǥ��. 
   ���� ���� ����� ������ ���� ���ٸ�, ���� ��ȯ.	 */
int Move(int r, int c, int unionNum)
{
	memset(visited, false, sizeof(visited));

	q.push({ r, c });
	visited[r][c] = true;
	together[r][c] = unionNum;

	int totalCnt = 1;
	int totalPop = map[r][c];
	while (!q.empty())
	{
		int cur_r = q.front().first;
		int cur_c = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			int next_r = cur_r + dir[i][0];
			int next_c = cur_c + dir[i][1];
			if (next_r < 0 || next_c < 0 || next_r >= n || next_c >= n) continue;
			if (visited[next_r][next_c] || together[next_r][next_c]) continue;
			// �湮�ߴ� ������ �̹� ������ ���� �н�. (���� �����ϸ��� ����.)

			int diff = MyAbs(map[cur_r][cur_c] - map[next_r][next_c]);
			if (diff >= L && diff <= R) // ���� ������ �����ϸ�, ť�� ����.
			{
				totalCnt++;
				totalPop += map[next_r][next_c];
				
				q.push({ next_r, next_c });
				visited[next_r][next_c] = true;
				together[next_r][next_c] = unionNum;
			}
		}
	}
	
	// ���� ���� ���� �� �α� �̵� ���� ��ȯ.
	population[unionNum] = totalPop / totalCnt;
	if (totalCnt > 1) return 1;
	else		      return 0;
}

int main()
{
	scanf("%d %d %d", &n, &L, &R);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			scanf("%d", &map[i][j]);

	int answer = 0;
	while (1)
	{
		// 1. ���� �迭 �� ���� ���� �ʱ�ȭ.
		memset(together, 0, sizeof(together));

		// 2. ������ ���� Ȯ���ϱ�.
		int unionNum = 1; // ���� ��ȣ
		int unionCnt = 0; // ���� ��
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (!together[i][j]) // ���� ������, ����.
					unionCnt += Move(i, j, unionNum++);
			}
		}

		// 3. ���ձ��� ���ٸ�, Ż��.
		if (!unionCnt) break;
		
		// 4. �α� �̵� ����.
		answer++;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
				map[i][j] = population[together[i][j]];
		}
	}
	printf("%d", answer);

	return 0;
}
