#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

const int MAX = 7;
const int SIZE = 5;

int answer;
char map[SIZE][SIZE]; // �Է� ���� ����.
bool visited[SIZE][SIZE];
int dr[4] = { -1, 1, 0, 0 };
int dc[4] = { 0, 0, -1, 1 };

int time = 0;

/* ĥ�����Ŀ� ������ ģ�����, �� ��ȯ. */
bool CanMember(int num, int member)
{
	memset(visited, false, sizeof(visited));

	queue<int> q;
	q.push(num);
	visited[num / 5][num % 5] = true;

	int cnt = 0;
	while (!q.empty())
	{
		int cur = q.front();
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			int nr = (num / SIZE) + dr[i];
			int nc = (num % SIZE) + dc[i];
			int nnum = (nr * SIZE) + nc;
			if (nr < 0 || nc < 0 || nr >= SIZE || nc >= SIZE) continue;
			if (visited[nr][nc]) continue;

			if (member & (1 << nnum))
			{
				cnt++;
				q.push(nnum);
				visited[nr][nc] = true;
			}
		}
	}
	if (cnt == MAX) return true;
	else			return false;

	/*for (int i = 0; i < 4; i++)
	{
		int nr = (num / SIZE) + dr[i];
		int nc = (num % SIZE) + dc[i];
		int nnum = (nr * SIZE) + nc;
		if (nr < 0 || nc < 0 || nr >= SIZE || nc >= SIZE) continue;
		if (member & (1 << nnum)) return true;
	}
	return false;*/
}

/* ĥ������ ����� ���� �� �ִ� ��� ����� �� ã��. */
void FindMember(int num, int cnt, int yCnt, int member)
{
	if (yCnt >= 4) return; // Ż�� 1: �ӵ����İ� ����, ����.
	if (cnt == MAX)		   // Ż�� 2: ĥ���� (�����ϸ� ����).
	{
		time++;
		if (time == 3512)
		{
			for (int i = 0; i < SIZE * SIZE; i++)
			{
				if (member & (1 << i)) printf("1");
				else printf("0");
			}
			printf("\n[%d]\n", num);
		}
		if (CanMember(num, member)) answer++;
		return; // �����ϸ�, ����.
	}

	for (int i = num + 1; i < SIZE * SIZE; i++) // ������ ��� ã��.
	{
		if (member & (1 << i)) continue;		// �湮 üũ.
		//if (!CanMember(i, member)) continue; // ���� üũ.

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

	for(int i = 0; i < SIZE * SIZE; i++)
	{
		int add = 0;
		if (map[i / SIZE][i % SIZE] == 'Y') add++;
		FindMember(i, 1, add, 1 << i);
	}
	printf("%d\n", answer);
	return 0;
}