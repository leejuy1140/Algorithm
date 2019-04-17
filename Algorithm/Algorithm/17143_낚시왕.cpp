#include <iostream>
#include <vector>
using namespace std;

const int MAX = 101;
const int DEAD = -1;

int R, C, M;
int dir[5][2] = { {0, 0}, {-1, 0}, {1, 0}, {0, 1}, {0, -1} };

int map[MAX][MAX]; // 물고기 번호 저장.
struct Shark { int r, c, s, d, z; }; // 속력, 이동 방향, 크기.
vector<Shark> shark; // 해당 위치에 있는 물고기 저장.

int ReverseDir(int dir)
{
	if (dir == 1) return 2;
	if (dir == 2) return 1;
	if (dir == 3) return 4;
	if (dir == 4) return 3;
}

/* 잡은 물고기 죽인 후, 크기 반환. */
int Killshark(int c)
{
	for (int r = 1; r <= R; r++)
	{
		if (map[r][c])
		{
			int sharkSize = map[r][c];
			for (int i = 0; i < shark.size(); i++)
			{
				if (shark[i].z == sharkSize)
				{
					shark[i].z = DEAD;
					break;
				}
			}
			map[r][c] = 0;
			return sharkSize;
		}
	}
	return 0;
}

/* 살아있는 물고기들 위치 옮기기. */
void Moveshark()
{
	// 1. 물고기들의 위치 전부 0으로 설정.
	for (int i = 0; i < shark.size(); i++)
	{
		if (shark[i].z == DEAD) continue;
		map[shark[i].r][shark[i].c] = 0;
	}

	for (int i = 0; i < shark.size(); i++)
	{
		if (shark[i].z == DEAD) continue;

		/*// 2. 물고기 이동 1
		// 시간: 물고기 속도와 비례. -> 최대 1000.
		for (int k = 0; k < shark[i].s; k++)
		{
			int nr = shark[i].r + dir[shark[i].d][0];
			int nc = shark[i].c + dir[shark[i].d][1];
			if (nr < 1 || nc < 1 || nr > R || nc > C)
			{
				shark[i].d = ReverseDir(shark[i].d);
				shark[i].r += dir[shark[i].d][0];
				shark[i].c += dir[shark[i].d][1];
			}
			else
			{
				shark[i].r = nr;
				shark[i].c = nc;
			}
		}*/

		// 2. 물고기 이동 2
		// 주기는 12345654321처럼 2(R-1)과 2(C-1)로 구할 수 있음.
		// 따라서 물고기는 한 주기만 구하면, 나머지 위치도 동일.
		// 시간: 2 * (배열 크기 - 1) -> 최대 20.
		/*if (shark[i].d < 3)
		{
			int cycle = 2 * (R - 1);
			int move = shark[i].s % cycle;
			while (move--)
			{
				if (shark[i].d == 1 && shark[i].r == 1) shark[i].d = 2;
				if (shark[i].d == 2 && shark[i].r == R) shark[i].d = 1;
				shark[i].r += dir[shark[i].d][0];
			}
		}
		else
		{
			int cycle = 2 * (C - 1);
			int move = shark[i].s % cycle;
			while (move--)
			{
				if (shark[i].d == 3 && shark[i].c == C) shark[i].d = 4;
				if (shark[i].d == 4 && shark[i].c == 1) shark[i].d = 3;
				shark[i].c += dir[shark[i].d][1];
			}
		}*/

		// 3. 물고기 이동 3
		//  6  5  4  3 2 1 2 3 4 5 6 5 4 3  2  1
		// -------------------------			  1set: 2 - (음수)
		//               -----------------------  1set: 12 - (양수)
		// -4 -3 -2 -1 0 1 2 3 4 5 6 7 8 9 10 11
		// 시간: (물고기 속도 / 배열 크기)로 줄어듦. -> 최대 10.
		shark[i].r += (dir[shark[i].d][0] * shark[i].s);
		shark[i].c += (dir[shark[i].d][1] * shark[i].s);
		while (shark[i].r < 1 || shark[i].r > R)
		{
			if (shark[i].r > R) shark[i].r = (2 * R) - shark[i].r;
			else if (shark[i].r < 1) shark[i].r = 2 - shark[i].r;
			shark[i].d = ReverseDir(shark[i].d);
		}
		while (shark[i].c < 1 || shark[i].c > C)
		{
			if (shark[i].c > C) shark[i].c = (2 * C) - shark[i].c;
			else if (shark[i].c < 1) shark[i].c = 2 - shark[i].c;
			shark[i].d = ReverseDir(shark[i].d);
		}

		// 3. 현재 위치에 이미 물고기가 있는데 나보다 작다면 잡아먹고, 크다면 잡아먹힘.
		if (map[shark[i].r][shark[i].c])
		{
			if (map[shark[i].r][shark[i].c] < shark[i].z)
			{
				int prevSize = map[shark[i].r][shark[i].c];
				for (int k = 0; k < shark.size(); k++)
				{
					if (shark[k].z == prevSize)
					{
						shark[k].z = DEAD;
						break;
					}
				}
				map[shark[i].r][shark[i].c] = shark[i].z;
			}
			else shark[i].z = DEAD;
		}
		else map[shark[i].r][shark[i].c] = shark[i].z;
	}
}

int main()
{
	scanf("%d %d %d", &R, &C, &M);
	for (int i = 0; i < M; i++)
	{
		int r, c, s, d, z;
		scanf("%d %d %d %d %d", &r, &c, &s, &d, &z);
		shark.push_back({ r, c, s, d, z });
		map[r][c] = z;
	}

	int kill = 1;
	int answer = 0;
	while (kill <= C)
	{
		answer += Killshark(kill);
		Moveshark();
		kill++;
	}
	printf("%d", answer);

	return 0;
}