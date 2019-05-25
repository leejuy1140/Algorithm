/*
1) 문제 이해
1. 사탕의 색이 다른 인접한 두 칸 선택.
2. 두 칸 교환.
3. 같은 색으로 이루어져 있는 가장 긴 연속 부분 선택.

2) 설계 (완전 탐색)
1. 서로 색이 다른 인접한 두 칸 dfs로 선택. (행, 열 따로 수행.)
2. 색을 교환한 후 가장 긴 연속 부분을 구함.

*/

#include <iostream>
#include <algorithm>
using namespace std;

const int MAX = 51;

int n, answer;
char map[MAX][MAX];
int dir[2][2] = { {1, 0}, {0, 1} }; // 아래, 오른쪽 칸과 교환.


/* 현재 행의 가장 긴 사탕의 길이를 구하고 정답 갱신. */
void longestCandyRow(int r)
{
	int eat = 1;
	bool flag = false; // 연속 체크 중이면, true.
	for (int c = 1; c <= n; c++) // 마지막 칸도 연속인 경우, 정답에 반영하기 위해.
	{
		if (map[r][c - 1] == map[r][c])
		{
			if (!flag) flag = true;
			eat++;
		}
		else if (flag)
		{
			answer = max(answer, eat);
			flag = false;
			eat = 1;
		}
	}
}

/* 현재 열의 가장 긴 사탕의 길이를 구하고 정답 갱신. */
void longestCandyCol(int c)
{
	int eat = 1;
	bool flag = false; // 연속 체크 중이면, true.
	for (int r = 1; r <= n; r++)  // 마지막 칸도 연속인 경우, 정답에 반영하기 위해.
	{
		if (map[r - 1][c] == map[r][c])
		{
			if (!flag) flag = true;
			eat++;
		}
		else if (flag)
		{
			answer = max(answer, eat);
			flag = false;
			eat = 1;
		}
	}
}

void selectCandy(int r, int c)
{
	for (int i = 0; i < 2; i++)
	{
		int nr = r + dir[i][0];
		int nc = c + dir[i][1];
		if (nr < 0 || nc < 0 || nr >= n || nc >= n) continue;
		if (map[r][c] == map[nr][nc]) continue; // 다른 색 사탕만 교환 가능.

		swap(map[r][c], map[nr][nc]); // 교환.
		if (i) // 상하 교환 -> r, c, nc
		{
			longestCandyRow(r);
			longestCandyCol(c);
			longestCandyCol(nc);
		}
		else    // 좌우 교환 -> c, r, nr
		{
			longestCandyCol(c);
			longestCandyRow(r);
			longestCandyRow(nr);
		}
		swap(map[r][c], map[nr][nc]); // 원상 복구.
	}

	if (c + 1 < n) return selectCandy(r, c + 1);
	else
	{
		if (r + 1 < n) return selectCandy(r + 1, 0);
		else		   return;
	}
}

int main()
{
	cin >> n;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> map[i][j];

	// +) 처음 사탕의 길이가 가장 길 수도 있음.
	for (int i = 0; i < n; i++)
	{
		longestCandyRow(i);
		longestCandyCol(i);
	}

	selectCandy(0, 0);
	cout << answer << endl;
	return 0;
}