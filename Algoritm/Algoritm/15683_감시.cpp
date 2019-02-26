#include <stdio.h>
#include <vector>
#include <cstring>
using namespace std;

const int MAX = 10;
const int WALL = 6;
const int WATCH = 7;

int n, m, cctvCnt, minArea = 100, map[MAX][MAX];
int cctv[5][4][4][2] = { // cctv 종류, 감시 방향, 화살표 개수, 좌표
	{ {{-1, 0}}, {{1, 0}}, {{0, 1}}, {{0, -1}} }, // 1
	{ {{-1, 0}, {1, 0}}, {{0, 1}, {0, -1}} },	  // 2
	{ {{-1, 0}, {0, 1}},						  // 3
	  {{0, 1}, {1, 0}},	
	  {{1, 0}, {0, -1}},
	  {{0, -1}, {-1, 0}} },
	{ {{-1, 0}, {0, -1}, {0, 1}},				  // 4
	  {{0, -1}, {0, 1}, {1, 0}},
	  {{-1, 0}, {1, 0}, {0, -1}},
	  {{-1, 0}, {1, 0}, {0, 1}} },
	{ {{-1, 0}, {1, 0}, {0, 1}, {0, -1}} }		  // 5
};

bool isCCTV(int cam)
{ return (cam >= 1 && cam <= 5); }

int getDirCnt(int cam)
{
	if (cam == 2) return 2;
	if (cam == 5) return 1;
	return 4;
}

int getArrowCnt(int cam)
{
	if (cam == 1) return 1;
	if (cam == 2) return 2;
	return cam - 1;
}

void setCCTV(int r, int c, int curCnt, int curDir)
{
	if (curCnt > cctvCnt) return;

	/* map[r][c]의 cctv로 인해 감시되는 지역 표시. */
	int arrowCnt = getArrowCnt(map[r][c]);
	for (int i = 0; i < arrowCnt; i++)
	{
		int rr = r, cc = c;
		while (1)
		{
			rr += cctv[map[r][c] - 1][curDir][i][0];
			cc += cctv[map[r][c] - 1][curDir][i][1];
			if (rr < 1 || cc < 1 || rr > n || cc > m) break;
			if (map[rr][cc] == WALL) break;
			if (isCCTV(map[rr][cc]) || map[rr][cc] == WATCH) continue;
			map[rr][cc] = WATCH;
  		}
	}

	/* 사각지대 카운팅 & 최소 크기 갱신. */
	if (curCnt == cctvCnt)
	{
		int curArea = 0;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				if (!map[i][j]) curArea++;
		if (minArea > curArea) minArea = curArea;
		return;
	}

	/* 현재 감시 상태 저장. */
	int curMap[MAX][MAX];
	for (int k = 1; k <= n; k++)
		memcpy(curMap[k], map[k], sizeof(int) * (m + 1));

	/* 다음 cctv 설정. */
	int rr = r, cc = c + 1;
	if (cc > m) { rr++; cc = 1; }

	for (int i = rr; i <= n; i++)
	{
		for (int j = cc; j <= m; j++)
		{
			if (isCCTV(map[i][j]))
			{
				int dirCnt = getDirCnt(map[i][j]);
				for (int k = 0; k < dirCnt; k++)
				{
					setCCTV(i, j, curCnt + 1, k);
					for (int h = 1; h <= n; h++)
						memcpy(map[h], curMap[h], sizeof(int) * (m + 1));
				}
			}
		}
		cc = 1;
	}
}


int main()
{
	int sr = 0, sc = 0;
	int oriMap[MAX][MAX];
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			scanf("%d", &map[i][j]);
			oriMap[i][j] = map[i][j];
			if (isCCTV(map[i][j]))
			{
				cctvCnt++;
				if (!sr && !sc) { sr = i; sc = j; }
			}
		}
	}
	if (!cctvCnt)
	{
		int curArea = 0;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				if (!map[i][j]) curArea++;
		printf("%d\n", curArea);
		return 0;
	}

	int dirCnt = getDirCnt(map[sr][sc]);
	for (int i = 0; i < dirCnt; i++)
	{
		setCCTV(sr, sc, 1, i);
		for (int k = 1; k <= n; k++)
			memcpy(map[k], oriMap[k], sizeof(int) * (m + 1));
	}
	if (minArea == 100) minArea = 0;
	printf("%d\n", minArea);

	return 0;
}