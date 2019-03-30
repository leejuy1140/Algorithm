#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

const int MAX = 7;
const int SIZE = 5;

int answer;
char map[SIZE][SIZE]; // 입력 정보 저장.
bool visited[SIZE][SIZE];
int dr[4] = { -1, 1, 0, 0 };
int dc[4] = { 0, 0, -1, 1 };

/* 7명의 멤버들이 서로 인접했다면, 참 반환. */
bool CanMember(int num, int member)
{
	queue<int> q;
	q.push(num);

	int visited = 0;
	visited |= (1 << num);

	int cnt = 1;
	while (!q.empty())
	{
		int cur = q.front();
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			int nr = (cur / SIZE) + dr[i];
			int nc = (cur % SIZE) + dc[i];
			int nnum = (nr * SIZE) + nc;
			if (nr < 0 || nc < 0 || nr >= SIZE || nc >= SIZE) continue;
			if (visited & (1 << nnum)) continue;

			if (member & (1 << nnum))
			{
				cnt++;
				q.push(nnum);
				visited |= (1 << nnum);
			}
		}
	}
	if (cnt == MAX) return true;
	else			return false;
}

/* 칠공주파 멤버를 만들 수 있는 모든 경우의 수 찾기. */
void FindMember(int num, int cnt, int yCnt, int member)
{
	if (yCnt >= 4) return; // 탈출 1: 임도연파가 우위, 종료.
	if (cnt == MAX)	       // 탈출 2: 칠공주 (인접하면 정답).
	{
		if (CanMember(num, member)) answer++;
		return;
	}

	for (int i = num + 1; i < SIZE * SIZE; i++) // 나머지 멤버 찾기.
	{
		if (member & (1 << i)) continue;		// 방문 체크.

		int add = 0;
		if (map[i / SIZE][i % SIZE] == 'Y') add++;
		FindMember(i, cnt + 1, yCnt + add, member | (1 << i));
	}
}

int main()
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
			scanf("%1c", &map[i][j]);
		getchar();
	}

	// 첫 번째 자리에 앉은 친구부터 칠공주파로 선택.
	for (int i = 0; i < SIZE * SIZE; i++)
	{
		int add = 0;
		if (map[i / SIZE][i % SIZE] == 'Y') add++;
		FindMember(i, 1, add, 1 << i);
	}
	printf("%d\n", answer);
	return 0;
}