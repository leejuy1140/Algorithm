#include <stdio.h>

int direction[8][2] = { {0, 1}, {0, -1}, {-1, 0}, {1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };

int GetDirectionIdx(char _order[])
{
	if (_order[0] == 'R')
	{
		if (_order[1] == 'T') return 4;
		if (_order[1] == 'B') return 6;
		return 0;
	}
	if (_order[0] == 'L')
	{
		if (_order[1] == 'T') return 5;
		if (_order[1] == 'B') return 7;
		return 1;
	}
	if (_order[0] == 'B') return 2;
	if (_order[0] == 'T') return 3;
}

int main()
{
	int king_r, stone_r;
	char king_c, stone_c;
	scanf("%1c%1d", &king_c, &king_r);
	getchar(); scanf("%1c%1d", &stone_c, &stone_r);

	int moveCnt;
	scanf("%d", &moveCnt);
	for (int i = 0; i < moveCnt; i++)
	{
		char order[5];
		getchar(); scanf("%s", order);
		
		int dir = GetDirectionIdx(order);
		int next_king_r = king_r + direction[dir][0];
		char next_king_c = king_c + direction[dir][1];
		
		// 킹이 체스판 밖으로 나가는 경우.
		if (next_king_r < 1 || next_king_c - 'A' + 1 < 1) continue;
		if (next_king_r >= 9 || next_king_c - 'A' + 1 >= 9) continue;

		// 이동할 곳에 돌이 있는 경우.
		if (next_king_r == stone_r && next_king_c == stone_c)
		{
			int next_stone_r = stone_r + direction[dir][0];
			char next_stone_c = stone_c + direction[dir][1];
			
			// 돌이 체스판 밖으로 나가는 경우.
			if (next_stone_r < 1 || next_stone_c - 'A' + 1 < 1) continue;
			if (next_stone_r >= 9 || next_stone_c - 'A' + 1 >= 9) continue;

			stone_r = next_stone_r;
			stone_c = next_stone_c;
		}
		king_r = next_king_r;
		king_c = next_king_c;
	}
	printf("%c%d\n", king_c, king_r);
	printf("%c%d\n", stone_c, stone_r);

	return 0;
}