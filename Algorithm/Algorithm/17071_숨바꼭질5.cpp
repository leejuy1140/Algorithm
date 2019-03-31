#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

const int MAX = 500001;

/* �����̰� Ư�� ��ġ�� ó�� ������ �ð��� ¦��, Ȧ���� �����ؼ� ����.
   �����̴� Ư�� ĭ�� �����ϸ�, +1 -> -1�� �ݺ��ϸ� ������ ��ٸ� �� ����.
   ���� ���, �����̰� Ư�� ĭ�� ¦�� �ð��� �̸� �����߰�,
   ������ ¦�� �ð��� �ش� ĭ�� ������ �����̶��,
   �����̴� +1 -> -1�� �ݺ��ϸ�, �ش� ĭ���� ������ ���� �� ����. */
int subin[2][MAX]; // 0: ¦�� �ð�, 1: Ȧ�� �ð�

/* �����̰� Ư�� ĭ�� ó������ �����ϴ� �ð��� ¦Ȧ�� �����Ͽ� Ȯ��. */
void CheckSubin(int start)
{
	memset(subin, -1, sizeof(subin));

	queue<pair<int, int>> q; // �ð�, ��ġ.
	q.push(make_pair(0, start));
	subin[0][start] = 0;

	while (!q.empty())
	{
		int curTime = q.front().first;
		int curPos = q.front().second;
		q.pop();

		int next1 = curPos + 1;
		if (next1 < MAX && next1 >= 0)
		{
			if (subin[(curTime + 1) % 2][next1] == -1)
			{
				q.push(make_pair(curTime + 1, next1));
				subin[(curTime + 1) % 2][next1] = curTime + 1;
			}
		}

		int next2 = curPos - 1;
		if (next2 < MAX && next2 >= 0)
		{
			if (subin[(curTime + 1) % 2][next2] == -1)
			{
				q.push(make_pair(curTime + 1, next2));
				subin[(curTime + 1) % 2][next2] = curTime + 1;
			}
		}

		int next3 = curPos * 2;
		if (next3 < MAX && next3 >= 0)
		{
			if (subin[(curTime + 1) % 2][next3] == -1)
			{
				q.push(make_pair(curTime + 1, next3));
				subin[(curTime + 1) % 2][next3] = curTime + 1;
			}
		}
	}
}

/* ������ �ð��� ���� ��ġ��Ű��, 
   �����̰� ���� �����߾��ٸ�, ���� ������ �ð��� ����. */
int CheckSister(int cur, int move, int time)
{
	if (cur >= MAX) return -1; // ������ ������ �����, ����.
	if (subin[time % 2][cur] != -1 && subin[time % 2][cur] <= time) return time;
	return CheckSister(cur + move, move + 1, time + 1);
}

int main(void)
{
	int n, k;
	cin >> n >> k;
	CheckSubin(n);				  // ���� ���� Ȯ��.
	cout << CheckSister(k, 1, 0); // ���� Ȯ��.
	return 0;
}