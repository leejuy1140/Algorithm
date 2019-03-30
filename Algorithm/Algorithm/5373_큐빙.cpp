#include <stdio.h>
#include <algorithm>
using namespace std;

char cube[6][3][3] = {
	{{'w', 'w', 'w'}, {'w', 'w', 'w'}, {'w', 'w', 'w'}},
	{{'g', 'g', 'g'}, {'g', 'g', 'g'}, {'g', 'g', 'g'}},
	{{'r', 'r', 'r'}, {'r', 'r', 'r'}, {'r', 'r', 'r'}},
	{{'b', 'b', 'b'}, {'b', 'b', 'b'}, {'b', 'b', 'b'}},
	{{'y', 'y', 'y'}, {'y', 'y', 'y'}, {'y', 'y', 'y'}},
	{{'o', 'o', 'o'}, {'o', 'o', 'o'}, {'o', 'o', 'o'}},
};

int r[9] = { 0, 0, 0, 1, 1, 1, 2, 2, 2 }; // 큐브 블록 좌표
int c[9] = { 0, 1, 2, 0, 1, 2, 0, 1, 2 };

// 한 면을 시계 방향으로 돌릴 때, 블록 이동 방향.
int clock[9] = { 6, 3, 0, 7, 4, 1, 8, 5, 2 };
int unclock[9] = { 2, 5, 8, 1, 4, 7, 0, 3, 6 };

// {큐브 인덱스, 블록 좌표 인덱스} -> 시계 방향 순
int influence[6][12][2] = {
	{{2, 0}, {2, 1}, {2, 2}, {1, 0}, {1, 1}, {1, 2}, {5, 0}, {5, 1}, {5, 2}, {3, 0}, {3, 1}, {3, 2}},
	{{0, 0}, {0, 3}, {0, 6}, {2, 0}, {2, 3}, {2, 6}, {4, 0}, {4, 3}, {4, 6}, {5, 8}, {5, 5}, {5, 2}},
	{{0, 6}, {0, 7}, {0, 8}, {3, 0}, {3, 3}, {3, 6}, {4, 2}, {4, 1}, {4, 0}, {1, 8}, {1, 5}, {1, 2}},
	{{0, 8}, {0, 5}, {0, 2}, {5, 0}, {5, 3}, {5, 6}, {4, 8}, {4, 5}, {4, 2}, {2, 8}, {2, 5}, {2, 2}},
	{{2, 6}, {2, 7}, {2, 8}, {3, 6}, {3, 7}, {3, 8}, {5, 6}, {5, 7}, {5, 8}, {1, 6}, {1, 7}, {1, 8}},
	{{0, 2}, {0, 1}, {0, 0}, {1, 0}, {1, 3}, {1, 6}, {4, 6}, {4, 7}, {4, 8}, {3, 8}, {3, 5}, {3, 2}},
};

int getCubeIdx(char p)
{
	if (p == 'U') return 0;
	if (p == 'L') return 1;
	if (p == 'F') return 2;
	if (p == 'R') return 3;
	if (p == 'D') return 4;
	if (p == 'B') return 5;
}

void rollCube(int mainCube, char dir)
{
	char saveMainCube[9];
	for (int i = 0; i < 9; i++)
		saveMainCube[i] = cube[mainCube][r[i]][c[i]];

	char saveInflCube[18], add;
	for (int i = 0; i < 18; i++)
	{
		if (i < 3)		 add = 9;
		else if (i < 15) add = -3;
		else			 add = -15;

		int cc = influence[mainCube][i + add][0];
		int pp = influence[mainCube][i + add][1];
		saveInflCube[i] = cube[cc][r[pp]][c[pp]];
	}

	if (dir == '+')
	{
		/* 기준 면 회전. */
		for(int i = 0; i < 9; i++)
			cube[mainCube][r[i]][c[i]] = saveMainCube[clock[i]];

		/* 기준 면 회전으로 영향받는 칸들 회전. */
		for (int i = 0; i < 12; i++)
		{
			int cc = influence[mainCube][i][0];
			int pp = influence[mainCube][i][1];
			cube[cc][r[pp]][c[pp]] = saveInflCube[i];
		}
	}
	else
	{
		for (int i = 0; i < 9; i++)
			cube[mainCube][r[i]][c[i]] = saveMainCube[unclock[i]];

		for (int i = 6; i < 18; i++)
		{
			int cc = influence[mainCube][i - 6][0];
			int pp = influence[mainCube][i - 6][1];
			cube[cc][r[pp]][c[pp]] = saveInflCube[i];
		}
	}
}

int main()
{
	char copy[6][3][3]; // 처음 큐브 복사본
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++)
				copy[i][j][k] = cube[i][j][k];
	int t;
	scanf("%d", &t);
	for (int tt = 0; tt < t; tt++)
	{
		int n;
		scanf("%d", &n);
		for (int nn = 0; nn < n; nn++)
		{
			char plane, rollDir;
			getchar();
			scanf("%1c%1c", &plane, &rollDir);

			int cubeIdx = getCubeIdx(plane);
			rollCube(cubeIdx, rollDir);
		}

		for (int i = 0; i < 3; i++) // 출력
		{
			for (int j = 0; j < 3; j++)
				printf("%c", cube[0][i][j]);
			printf("\n");
		}
		for (int i = 0; i < 6; i++) // 큐브 초기화
			for (int j = 0; j < 3; j++)
				for (int k = 0; k < 3; k++)
					cube[i][j][k] = copy[i][j][k];
	}

	return 0;
}