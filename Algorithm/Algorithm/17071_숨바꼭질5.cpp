#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

const int MAX = 500001;

/* 수빈이가 특정 위치에 처음 도달한 시간을 짝수, 홀수를 구분해서 저장.
   수빈이는 특정 칸에 도달하면, +1 -> -1을 반복하며 동생을 기다릴 수 있음.
   예를 들어, 수빈이가 특정 칸에 짝수 시간에 미리 도달했고,
   동생도 짝수 시간에 해당 칸에 도착할 예정이라면,
   수빈이는 +1 -> -1을 반복하며, 해당 칸에서 동생을 만날 수 있음. */
int subin[2][MAX]; // 0: 짝수 시간, 1: 홀수 시간

/* 수빈이가 특정 칸에 처음으로 도달하는 시간을 짝홀을 구분하여 확인. */
void CheckSubin(int start)
{
	memset(subin, -1, sizeof(subin));

	queue<pair<int, int>> q; // 시간, 위치.
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

/* 동생을 시간에 따라 위치시키며, 
   수빈이가 먼저 도착했었다면, 현재 동생의 시간이 정답. */
int CheckSister(int cur, int move, int time)
{
	if (cur >= MAX) return -1; // 동생이 범위를 벗어나면, 종료.
	if (subin[time % 2][cur] != -1 && subin[time % 2][cur] <= time) return time;
	return CheckSister(cur + move, move + 1, time + 1);
}

int main(void)
{
	int n, k;
	cin >> n >> k;
	CheckSubin(n);				  // 수빈 먼저 확인.
	cout << CheckSister(k, 1, 0); // 동생 확인.
	return 0;
}