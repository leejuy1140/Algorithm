#include <stdio.h>
#include <vector>
using namespace std;

const int MAX = 101;

vector<int> dragon; // �巡��Ŀ���� ���� ����.
int n, map[MAX][MAX];
int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, -1, 0, 1 };

int main()
{
	scanf("%d", &n);
	while (n--)
	{
		int x, y, d, g;
		scanf("%d %d %d %d", &x, &y, &d, &g);

		// 0 ���� �׸���.
		map[y][x] = 1;
		y += dy[d];
		x += dx[d];
		map[y][x] = 1;
		dragon.push_back(d);

		// 1 ~ g ���� �׸���.
		for (int i = 1; i <= g; i++)
		{
			int idx = dragon.size() - 1;
			for (idx; idx >= 0; idx--)
			{
				int nd = (dragon[idx] + 1) % 4;
				y += dy[nd];
				x += dx[nd];
				map[y][x] = 1;
				dragon.push_back(nd);
			}
		}
		dragon.clear();
	}

	// ������ ���� �巡�� Ŀ���� ���� ���� ī����.
	int answer = 0;
	for (int i = 0; i < MAX - 1; i++)
	{
		for (int j = 0; j < MAX - 1; j++)
			if (map[i][j] && map[i + 1][j] && map[i][j + 1] && map[i + 1][j + 1]) answer++;
	}
	printf("%d", answer);
}