#include <stdio.h>

bool board[6][6];

// 나이트의 이동 범위가 맞으면, 참 반환.
bool CheckNight(int r, int c, int nr, int nc)
{
	int diff_r = r - nr;
	int diff_c = c - nc;
	if (diff_r == 2 || diff_r == -2)
	{
		if (diff_c == 1 || diff_c == -1) return true;
		else return false;
	}
	else
	{
		if (diff_c == 2 || diff_c == -2) return true;
		else return false;
	}
}

int main()
{
	int start_r; char start_c;
	scanf("%1c%1d", &start_c, &start_r);
	start_r--;
	start_c -= 'A';

	int prev_r = start_r;
	char prev_c = start_c;
	for (int i = 0; i < 35; i++)
	{
		getchar();
		int cur_r; char cur_c;
		scanf("%1c%1d", &cur_c, &cur_r);
		cur_r--;
		cur_c -= 'A';

		bool flag = CheckNight(prev_r, prev_c, cur_r, cur_c);
		if (!flag || board[cur_r][cur_c])
		{
			printf("Invalid");
			return 0;
		}

		board[cur_r][cur_c] = true;
		prev_r = cur_r;
		prev_c = cur_c;
	}

	bool flag = CheckNight(start_r, start_c, prev_r, prev_c);
	if (flag) printf("Valid");
	else	  printf("Invalid");

	return 0;
}