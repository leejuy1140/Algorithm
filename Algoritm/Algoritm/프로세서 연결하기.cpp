#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;

const int MAX = 12;
const int INF = 99999999;
const int WIRE = 2;

int n, minWireLen, board[MAX][MAX];
int direction[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

vector<int> selectedIdx; // 연결할 코어 선택.
vector<pair<int, int>> core; // 가장 자리 아닌 코어의 위치 저장.


/* 선택된 코어를 모두 전원에 연결하면, 최소 전선 길이 갱신. */
void ConnectWire(int _idx, int _dir, int _curWireLen)
{
	if (_idx == selectedIdx.size())
	{
		if (minWireLen > _curWireLen) minWireLen = _curWireLen;
		return;
	}

	// 1. 전선 연결.
	int add = 0; // 추가할 전선 길이.
	bool flag = 0; // 연결 실패 시, 1.

	int coreIdx = selectedIdx[_idx];
	int r = core[coreIdx].first;
	int c = core[coreIdx].second;
	while (1)
	{
		r += direction[_dir][0];
		c += direction[_dir][1];
		if (r < 0 || c < 0 || r >= n || c >= n) break;
		if (board[r][c]) { flag = 1; break; }

		add++;
		board[r][c] = WIRE;
	}
	if (flag) return; // 연결 실패 시, 종료.

	// 2. 전선 성공적 설치 후, 현재 보드 상태 저장.
	int copyBoard[MAX][MAX];
	for (int i = 0; i < n; i++)
		memcpy(&copyBoard[i], &board[i], sizeof(int) * n);

	// 3. 다음 코어 연결.
	for (int i = 0; i < 4; i++)
	{
		ConnectWire(_idx + 1, i, _curWireLen + add);
		for (int k = 0; k < n; k++)
			memcpy(&board[k], &copyBoard[k], sizeof(int) * n);
	}
}

/* 연결할 코어를 _remain이 0이 될 때까지 선택. */
void SelectCore(int _idx, int _remain)
{
	if (_idx + _remain >= core.size()) return;

	// 코어 선택 완료했으면, 전선 연결.
	if (_remain == 0)
	{
		int copyBoard[MAX][MAX]; // 현재 보드 상태 저장.
		for (int i = 0; i < n; i++)
			memcpy(&copyBoard[i], &board[i], sizeof(int) * n);

		for (int i = 0; i < 4; i++) // 첫 번째 코어부터 연결.
		{
			ConnectWire(0, i, 0);
			for (int k = 0; k < n; k++)
				memcpy(&board[k], &copyBoard[k], sizeof(int) * n);
		}
		return;
	}

	// 다음에 연결할 코어 찾기.
	for (int i = _idx + 1; i < core.size(); i++)
	{
		selectedIdx.push_back(i);
		SelectCore(i, _remain - 1);
		selectedIdx.pop_back();
	}
}

int main()
{
	int t;
	scanf("%d", &t);
	for (int T = 1; T <= t; T++)
	{
		minWireLen = INF;
		core.clear();
		selectedIdx.clear();

		scanf("%d", &n);
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				scanf("%d", &board[i][j]);
				if (i && j && i < n && j < n)
					if (board[i][j]) core.push_back(make_pair(i, j));
			}
		}
		
		/* 코어를 많이 연결하는 순으로, 체크. */
		for (int cnt = core.size(); cnt >= 1; cnt--)
		{
			for (int idx = 0; idx < core.size(); idx++)
			{
				selectedIdx.push_back(idx);
				SelectCore(idx, cnt - 1);
				selectedIdx.pop_back();
			}

			// 코어는 최대 선택이므로, 연결 가능하면, 탈출.
			if (minWireLen != INF) break;
		}
		printf("#%d %d\n", T, minWireLen);
	}

	return 0;
}