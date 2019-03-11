#include <stdio.h>
#include <string.h>
#include <deque>
#include <vector>
using namespace std;

const int MAX = 105;
const int INF = 99999999;

int n, m;
char map[MAX][MAX];
int open[MAX][MAX]; // 3���� ���� �� Ƚ���� ��.
bool visited[MAX][MAX]; // �湮 ���� üũ.
int dir[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

typedef pair<int, pair<int, int>> myPair;

void bfs(int r, int c)
{
	memset(visited, 0, sizeof(visited));
	
	deque<myPair> dq; // ���� �μ� Ƚ���� ���� �� ���� Ž��.
	dq.push_back(make_pair(0, make_pair(r, c)));
	visited[r][c] = 1;

	while (!dq.empty())
	{
		myPair cur = dq.front();
		dq.pop_front();

		for (int i = 0; i < 4; i++)
		{
			int nr = cur.second.first + dir[i][0];
			int nc = cur.second.second + dir[i][1];
			if (nr < 0 || nc < 0 || nr > n + 1 || nc > m + 1) continue;
			if (map[nr][nc] == '*' || visited[nr][nc]) continue;
			
			int ncnt = cur.first;
			if (map[nr][nc] == '#') // ���� ����� �Ѵٸ�, ���� �ڿ� ����.
			{
				open[nr][nc] += ncnt + 1;
				dq.push_back(make_pair(ncnt + 1, make_pair(nr, nc)));
			}
			else // �ƴ϶��, ���� �տ� ������ ���� Ž���� �� �ֵ���!
			{
				open[nr][nc] += ncnt;
				dq.push_front(make_pair(ncnt, make_pair(nr, nc)));
			}
			visited[nr][nc] = 1;
		}
	}
}

int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
	{
		vector<pair<int, int>> prisoner; // �˼��� ��ǥ.
		scanf("%d %d", &n, &m);
		for (int i = 1; i <= n; i++)
		{
			getchar();
			for (int j = 1; j <= m; j++)
			{
				scanf("%1c", &map[i][j]);
				if (map[i][j] == '$')
					prisoner.push_back(make_pair(i, j));
			}
		}
		// ��� �е�.
		for (int i = 0; i < n + 2; i++) map[i][0] = map[i][m + 1] = '.';
		for (int i = 0; i < m + 2; i++) map[0][i] = map[n + 1][i] = '.';

		bfs(0, 0);
		for (int i = 0; i < 2; i++)
			bfs(prisoner[i].first, prisoner[i].second);

		int minNum = INF;
		for (int i = 0; i < n + 2; i++)
		{
			for (int j = 0; j < m + 2; j++)
			{ 
				if (map[i][j] == '*') continue;

				// ���� �ѹ��� ���� �Ǳ� ������, -2.
				if (map[i][j] == '#') open[i][j] -= 2;
				if (minNum > open[i][j]) minNum = open[i][j];
			}
		}
		printf("%d\n", minNum);

		memset(open, 0, sizeof(open));
	}
	return 0;
}