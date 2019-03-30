#include <stdio.h>
#include <utility>
#include <cmath>
using namespace std;

const int MAX = 101;

int n, l, map[MAX][MAX];

int check(bool isRow)
{
	int road = 0;

	for (int fix = 0; fix < n; fix++)
	{
		pair<int, int> prev = make_pair(map[0][fix], 1); // 이전 높이, 같은 높이 개수.
		if (isRow) prev = make_pair(map[fix][0], 1);

		bool flag = 0; // 길 없으면, 1로 set.
		for (int move = 1; move < n; move++)
		{
			int curHeight = map[move][fix];
			if (isRow) curHeight = map[fix][move];

			if (prev.first == curHeight) prev.second++;
			else if (prev.first < curHeight && curHeight - prev.first == 1)
			{
				/* 1. 이전 높이에 경사로 설치하는데, l개 미만이면, 탈출. */
				if (prev.second >= l) prev = make_pair(curHeight, 1);
				else				  { flag = 1; break; }
			}
			else if (prev.first > curHeight && prev.first - curHeight == 1)
			{
				/* 2. 현재 높이에 경사로 설치하는데, l개 미만이면, 탈출. */
				prev = make_pair(curHeight, 1);
				for (int i = move + 1; i < n; i++)
				{
					int nextHeight = map[i][fix];
					if (isRow) nextHeight = map[fix][i];

					if (prev.first == nextHeight) prev.second++;
					else						  break;
				}
				if (prev.second >= l)
				{
					move += (prev.second - 1);
					prev.second -= l;
				}
				else { flag = 1; break; }
			}
			else { flag = 1; break; }
		}
		if (!flag) road++;
	}

	return road;
}

int main()
{
	scanf("%d %d", &n, &l);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			scanf("%d", &map[i][j]);

	int answer = check(0);
	answer += check(1);
	printf("%d\n", answer);

	return 0;
}