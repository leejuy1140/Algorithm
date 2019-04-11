#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;

const int MAX = 10;
const int INF = 9999999;
const int WALL = 6;
const int WATCH = -1;

int totalArea, minArea = INF;	// ���� �� �簢������ ũ��.
vector<pair<int, int>> cam;		// CCTV ��ġ ����.

int n, m, map[MAX][MAX];
int dr[5] = { 0, 0, -1, 0, 1 }; // ���ϵ���
int dc[5] = { 0, -1, 0, 1, 0 };
int cctv[6][4][4] = {			// �� cctv�� ���� ����.
	{{0}},
	{{1},		  {2},	   {3},		   {4}},	    // 1
	{{1, 3},	  {2, 4}},						    // 2
	{{1, 2},	  {2, 3},	   {3, 4},    {4, 1}},	// 3
	{{1, 2, 3},   {2, 3, 4}, {3, 4, 1}, {4, 1, 2}}, // 4
	{{1, 2, 3, 4}}								    // 5
};

/* CCTV�̸�, �� ��ȯ. */
bool CheckCCTV(int num)
{
	return (num >= 1 && num <= 5);
}

/* ���� CCTV ��ȣ�� �Է��ϸ�, ���� ������ ���� ���� ���� ��ȯ. */
pair<int, int> GetCCTVInfo(int cur)
{
	if (cur == 1) return { 4, 1 };
	if (cur == 2) return { 2, 2 };
	if (cur == 3) return { 4, 2 };
	if (cur == 4) return { 4, 3 };
	if (cur == 5) return { 1, 4 };
}

/* ���� CCTV ���� k��° ������ i��° �������� �������� ��,
   ���ô��ϴ� ĭ�� ���� ��ȯ.								*/
int Watch(int r, int c, int dir)
{
	int nr = r;
	int nc = c;
	int cnt = 0;
	while (1)
	{
		nr += dr[dir];
		nc += dc[dir];
		if (nr < 0 || nc < 0 || nr >= n || nc >= m) break;
		if (CheckCCTV(map[nr][nc])) continue; // CCTV ��� ����.
		if (map[nr][nc] == WALL) break;		  // �� ��� �Ұ���.

		// ���ô��ϰ� �ִ� ĭ�� �ƴ϶��,
		// ���� ǥ�� �� ���� ���ϴ� ĭ�� ���� ����.
		if (map[nr][nc] != WATCH)
		{
			map[nr][nc] = WATCH;
			cnt++;
		}
	}
	return cnt;
}

void dfs(int idx, int watchCnt)
{
	// ��� ī�޶��� ���� ������ �� ��������, �簢 ���� ���.
	if (idx == cam.size())
	{
		int curArea = totalArea - watchCnt;
		minArea = minArea < curArea ? minArea : curArea;
		return;
	}

	// 1. ���� ī�޶��� ���� ���� �� ���� ���� �ޱ�.
	int r = cam[idx].first;
	int c = cam[idx].second;
	int cam = map[r][c];
	pair<int, int> info = GetCCTVInfo(cam);

	// 2. ���� map�� ���� ����.
	int save[MAX][MAX];
	memcpy(save, map, sizeof(map));

	// 3. ���� ���� �� �ϳ� �����Ͽ�, ���� ����.
	for (int k = 0; k < info.first; k++)	  // ���� ����.
	{
		int curWatchCnt = 0;
		for (int i = 0; i < info.second; i++) // ���� ����.
			curWatchCnt += Watch(r, c, cctv[cam][k][i]);

		// 4. ���� ī�޶� ����.
		dfs(idx + 1, watchCnt + curWatchCnt);

		// 5. ���� ���� ���� ����
		memcpy(map, save, sizeof(map));
	}

}

int main()
{
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			scanf("%d", &map[i][j]);
			if (!map[i][j])			  totalArea++;
			if (CheckCCTV(map[i][j])) cam.push_back({ i, j });
		}
	}
	dfs(0, 0);
	printf("%d", minArea);
	return 0;
}