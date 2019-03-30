#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int MAX = 55;
const int INF = 99999999;

char map[MAX][MAX];
bool visited[MAX][MAX];
int n, altitude[MAX][MAX];
int dr[8] = { -1, 1, 0, 0, -1, -1, 1, 1 };
int dc[8] = { 0, 0, -1, 1, 1, -1, 1, -1 };

/* min_h와 max_h 범위 내로 배달가능한 집 수 반환. */
int dfs(int r, int c, int min_h, int max_h)
{
	if (r < 0 || c < 0 || r >= n || c >= n) return 0;
	if (visited[r][c]) return 0;
	if (altitude[r][c] < min_h) return 0;
	if (altitude[r][c] > max_h) return 0;

	visited[r][c] = 1;

	int ret = 0;
	if (map[r][c] == 'K') ret++;

	for (int i = 0; i < 8; i++)
	{
		int nr = r + dr[i];
		int nc = c + dc[i];
		ret += dfs(nr, nc, min_h, max_h);
	}
	return ret;
}

int main()
{
	vector<int> height;
	int post_r, post_c, houseCnt = 0;

	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		getchar();
		for (int j = 0; j < n; j++)
		{
			scanf("%1c", &map[i][j]);
			if (map[i][j] == 'P')
			{
				post_r = i;
				post_c = j;
			}
			if (map[i][j] == 'K') houseCnt++;
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			scanf("%d", &altitude[i][j]);
			height.push_back(altitude[i][j]);
		}
	}

	/* 1. 높이 정렬 및 중복 제거. */
	sort(height.begin(), height.end());
	height.erase(unique(height.begin(), height.end()), height.end());

	/* 2. height[i] ~ height[j]의 범위로 우편물 배달.
	i와 j는 0부터 시작하기 때문에,
	- 배달 가능: 최고도인 j가 충분하다는 뜻이므로, i++;
	- 배달 불가능: 최고도인 j로 부족하다는 뜻이므로, j++;	*/
	int i = 0, j = i, answer = INF;
	while (i < height.size() && j < height.size())
	{
		memset(visited, 0, sizeof(visited));
		int finishCnt = dfs(post_r, post_c, height[i], height[j]);
		if (finishCnt == houseCnt)
		{
			answer = min(answer, height[j] - height[i]);
			i++;
		}
		else j++;
	}
	printf("%d\n", answer);

	return 0;
}