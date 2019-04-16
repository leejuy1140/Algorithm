#include <iostream>
#include <vector>
using namespace std;

const int MAX = 101;
const int DEAD = -1;

int R, C, M;
int dir[5][2] = { {0, 0}, {-1, 0}, {1, 0}, {0, 1}, {0, -1} };

int map[MAX][MAX]; // ����� ��ȣ ����.
struct Shark { int r, c, s, d, z; }; // �ӷ�, �̵� ����, ũ��.
vector<Shark> shark; // �ش� ��ġ�� �ִ� ����� ����.

int ReverseDir(int dir)
{
	if (dir == 1) return 2;
	if (dir == 2) return 1;
	if (dir == 3) return 4;
	if (dir == 4) return 3;
}

/* ���� ����� ���� ��, ũ�� ��ȯ. */
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

/* ����ִ� ������ ��ġ �ű��. */
void Moveshark()
{
	// 1. �������� ��ġ ���� 0���� ����.
	for (int i = 0; i < shark.size(); i++)
	{
		if (shark[i].z == DEAD) continue;
		map[shark[i].r][shark[i].c] = 0;
	}

	for (int i = 0; i < shark.size(); i++)
	{
		if (shark[i].z == DEAD) continue;

		/*// 2. ����� �̵� 1
		// �ð�: ����� �ӵ��� ���.
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

		// 2. ����� �̵� 2
		// �ð�: (����� �ӵ� / �迭 ũ��)�� �پ��.
		int nr = shark[i].r + (dir[shark[i].d][0] * shark[i].s);
		int nc = shark[i].c + (dir[shark[i].d][1] * shark[i].s);
		while (nr < 1 || nr > R)
		{
			if (nr > R) nr = (2 * R) - nr;
			else if (nr < 1) nr = 2 - nr;
			shark[i].d = ReverseDir(shark[i].d);
		}
		while (nc < 1 || nc > C)
		{
			if (nc > C) nc = (2 * C) - nc;
			else if (nc < 1) nc = 2 - nc;
			shark[i].d = ReverseDir(shark[i].d);
		}

		// 3. ���� ��ġ�� �̹� ����Ⱑ �ִµ� ������ �۴ٸ� ��Ƹ԰�, ũ�ٸ� ��Ƹ���.
		shark[i].r = nr;
		shark[i].c = nc;
		if (map[nr][nc])
		{
			if (map[nr][nc] < shark[i].z)
			{
				int prevSize = map[nr][nc];
				for (int k = 0; k < shark.size(); k++)
				{
					if (shark[k].z == prevSize)
					{
						shark[k].z = DEAD;
						break;
					}
				}
				map[nr][nc] = shark[i].z;
			}
			else shark[i].z = DEAD;
		}
		else map[nr][nc] = shark[i].z;
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