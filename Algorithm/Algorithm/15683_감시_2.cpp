#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;

const int MAX = 10;
const int INF = 9999999;
const int WALL = 6;
const int WATCH = -1;

int totalArea, minArea = INF;	// 감시 전 사각지대의 크기.
vector<pair<int, int>> cam;		// CCTV 위치 저장.

int n, m, map[MAX][MAX];
int dr[5] = { 0, 0, -1, 0, 1 }; // 서북동남
int dc[5] = { 0, -1, 0, 1, 0 };
int cctv[6][4][4] = {			// 각 cctv의 감시 방향.
	{{0}},
	{{1},		  {2},	   {3},		   {4}},	    // 1
	{{1, 3},	  {2, 4}},						    // 2
	{{1, 2},	  {2, 3},	   {3, 4},    {4, 1}},	// 3
	{{1, 2, 3},   {2, 3, 4}, {3, 4, 1}, {4, 1, 2}}, // 4
	{{1, 2, 3, 4}}								    // 5
};

/* CCTV이면, 참 반환. */
bool CheckCCTV(int num)
{
	return (num >= 1 && num <= 5);
}

/* 현재 CCTV 번호를 입력하면, 감시 종류와 감시 방향 개수 반환. */
pair<int, int> GetCCTVInfo(int cur)
{
	if (cur == 1) return { 4, 1 };
	if (cur == 2) return { 2, 2 };
	if (cur == 3) return { 4, 2 };
	if (cur == 4) return { 4, 3 };
	if (cur == 5) return { 1, 4 };
}

/* 현재 CCTV 에서 k번째 감시의 i번째 방향으로 감시했을 때,
   감시당하는 칸의 개수 반환.								*/
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
		if (CheckCCTV(map[nr][nc])) continue; // CCTV 통과 가능.
		if (map[nr][nc] == WALL) break;		  // 벽 통과 불가능.

		// 감시당하고 있는 칸이 아니라면,
		// 감시 표시 후 감시 당하는 칸의 개수 증가.
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
	// 모든 카메라의 감시 방향을 다 정했으면, 사각 지대 계산.
	if (idx == cam.size())
	{
		int curArea = totalArea - watchCnt;
		minArea = minArea < curArea ? minArea : curArea;
		return;
	}

	// 1. 현재 카메라의 감시 종료 및 방향 개수 받기.
	int r = cam[idx].first;
	int c = cam[idx].second;
	int cam = map[r][c];
	pair<int, int> info = GetCCTVInfo(cam);

	// 2. 현재 map의 상태 저장.
	int save[MAX][MAX];
	memcpy(save, map, sizeof(map));

	// 3. 감시 종류 중 하나 선택하여, 감시 시작.
	for (int k = 0; k < info.first; k++)	  // 종류 선택.
	{
		int curWatchCnt = 0;
		for (int i = 0; i < info.second; i++) // 감시 방향.
			curWatchCnt += Watch(r, c, cctv[cam][k][i]);

		// 4. 다음 카메라 감시.
		dfs(idx + 1, watchCnt + curWatchCnt);

		// 5. 감시 상태 원상 복구
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