#include <stdio.h>
#include <utility>
using namespace std;

const int MAX = 105;

int map[MAX][MAX];
int dr[4] = { 1, 0, -1, 0 }; // L: -1, R: +1.
int dc[4] = { 0, -1, 0, 1 }; // 남서북동

pair<int, int> GetSize(bool row_col)
{
	int start = MAX, end = 0;
	for (int i = 0; i < MAX; i++)
	{
		bool flag = false;
		for (int j = 0; j < MAX; j++)
		{
			char tmp;
			if (row_col) tmp = map[i][j];
			else		 tmp = map[j][i];

			if (!flag && tmp)
			{
				start = start < j ? start : j;
				flag = true;
			}
			if (flag && tmp) end = end > j ? end : j;
		}
	}
	return make_pair(start, end + 1);
}

int main()
{
	int len;
	scanf("%d", &len);
	getchar();

	int r = 53, c = 53, dir = 0;
	map[r][c] = 1; // 시작 점은 중앙으로 설정.

	while (len--)
	{
		char order;
		scanf("%1c", &order);

		if (order == 'L')
		{
			dir--;
			if (dir < 0) dir = 3;
		}
		else if (order == 'F')
		{
			r += dr[dir];
			c += dc[dir];
			map[r][c] = 1;
		}
		else dir = (dir + 1) % 4;
	}

	pair<int, int> row = GetSize(0);
	pair<int, int> col = GetSize(1);
	for (int i = row.first; i < row.second; i++)
	{
		for (int j = col.first; j < col.second; j++)
		{
			if (map[i][j]) printf(".");
			else		   printf("#");
		}
		printf("\n");
	}
	return 0;
}