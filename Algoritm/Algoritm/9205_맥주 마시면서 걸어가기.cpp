#include <stdio.h>
#include <string.h>
#include <cmath>
#include <queue>
using namespace std;

const int MAX = 105;
const int FULL_BEER = 20;
const int PER_METER = 50;

// [0]: home, [1 ~ n]: ������, [n + 1]: �佺Ƽ��
int n, dist[MAX][MAX];
bool visited[MAX][MAX];
pair<int, int> location[MAX];

int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d", &n);
		scanf("%d %d", &location[0].first, &location[0].second);
		for(int i = 1; i <= n; i++)
			scanf("%d %d", &location[i].first, &location[i].second);
		scanf("%d %d", &location[n + 1].first, &location[n + 1].second);

		for (int i = 0; i <= n + 1; i++) // �� �ǹ����� �Ÿ�.
		{
			for (int j = i + 1; j <= n + 1; j++)
			{
				int dist_x = abs(location[i].first - location[j].first);
				int dist_y = abs(location[i].second - location[j].second);
				dist[i][j] = dist[j][i] = dist_x + dist_y;
			}
		}

		queue<pair<int, int>> q;
		q.push(make_pair(0, FULL_BEER)); // �ǹ� �ε���, ���� ��.

		bool flag = 0; // 1�̸�, happy;
		while (!q.empty())
		{
			pair<int, int> cur = q.front();
			q.pop();

			// �佺Ƽ�� �� �� ����.
			int needBeer = ceil((float)dist[cur.first][n + 1] / PER_METER);
			if (needBeer <= cur.second) { flag = 1; break; }

			for (int i = 1; i <= n; i++) // ������ �鸧.
			{
				needBeer = ceil((float)dist[cur.first][i] / PER_METER);
				if (needBeer > cur.second || visited[cur.first][i]) continue;

				visited[cur.first][i] = 1;
				q.push(make_pair(i, FULL_BEER));
			}
		}
		if (flag) printf("happy\n");
		else	  printf("sad\n");

		memset(visited, 0, sizeof(visited));
	}
	return 0;
}