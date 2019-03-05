#include <stdio.h>
#include <string.h>

const int CORE = 1;
const int WIRE = 2;

const int MAX = 12;
const int INF = 99999999;

int core[MAX][3]; // 0: 선택 여부, 1: r, 2: c
int n, coreCnt, curLen, minLen, board[MAX][MAX];
int direction[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

// 가장 자리에 위치하면, true 반환.
bool checkEdge(int r, int c)
{
	return (!r || !c || r >= n - 1 || c >= n - 1);
}

int SetWire(int r, int c, int dir)
{
	int rr = r;
	int cc = c;
	int len = 0;
	bool flag = 0; // 전선을 설치하지 못하면, 1.

	while (1)
	{
		rr += direction[dir][0];
		cc += direction[dir][1];
		if (rr < 0 || cc < 0 || rr >= n || cc >= n) break;
		if (board[rr][cc]) { flag = 1; break; }

		len++;
		board[rr][cc] = WIRE;
	}
	if (flag)
	{
		rr = r;
		cc = c;
		while (1)
		{
			rr += direction[dir][0];
			cc += direction[dir][1];
			if (rr < 0 || cc < 0 || rr >= n || cc >= n) break;
			if (board[rr][cc]) break;

			board[rr][cc] = 0;
		}
		len = 0;
	}

	return len;
}

int GetWireLength(int idx, int dir)
{
	// 1. 현재 core에서 dir 방향으로 전선 설치.
	// 전선을 설치하지 못한다면, 종료.
	int ret = SetWire(core[idx][1], core[idx][2], dir);
	if (!ret) return;


	// 다음에 연결할 core 찾기.
	for (int i = idx + 1; i < coreCnt; i++)
	{
		if (!core[i][0]) continue;
		if (checkEdge) continue;

		for (int j = 0; j < 4; j++)
		{
			GetWireLength(i, j);
			
		}
		break;
	}

	curLen -= addLen;
}

void SelectCore(int idx, int remain)
{
	core[idx][0] = 1;

	if (remain == 1)
	{
		for (int i = 0; i < coreCnt; i++)
		{
			if (!core[i][0]) continue;
			if (checkEdge) continue;

			for (int j = 0; j < 4; j++)
			{
				int save[MAX][MAX]
				GetWireLength(i, j);
				minLen = minLen < curLen ? minLen : curLen;
			}
			break;
		}
		return;
	}

	for (int i = idx; i < coreCnt; i++)
	{
		if (coreCnt - i < remain) break;
		
		SelectCore(i, remain - 1);
		core[i][0] = 0;
	}
}

int main()
{
	int t;
	scanf("%d", &t);
	for (int T = 1; T <= t; T++)
	{
		scanf("%d", &n); // 입력.
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				scanf("%d", &board[i][j]);
				if (board[i][j] == CORE)
				{
					core[coreCnt][0] = 0;
					core[coreCnt][1] = i;
					core[coreCnt][2] = j;
					coreCnt++;
				}
			}
		}
		
		// 모든 core ~ 1개.
		for (int i = coreCnt; i >= 1; i--)
		{
			for (int j = 0; j < coreCnt; j++)
			{
				if (coreCnt - j < coreCnt) break;
				
				SelectCore(j, i);
				core[j][0] = 0;
			}
			if (minLen != INF) break;
		}
		printf("#%d %d\n", T, minLen);

		minLen = INF; // 초기화.
		coreCnt = 0;
		for (int i = 0; i < n; i++)
		{
			memset(&board[i], 0, sizeof(int) * n);
			memset(&core[i], 0, sizeof(int) * 3);
		}
	}

	return 0;
}