#include <stdio.h>
#include <string.h>


int bingo[5][5];
bool my[5][5];

int line;
bool garo[5], sero[5], dia[2];

// �� ĭ�� ����, ���� �밢 Ȯ��
int checkBingo2(int x, int y)
{
	int r, c;

	// 1. ����
	if (!garo[y])
	{
		for (c = 0; c < 5; c++)
			if (!my[y][c]) break;

		if (c == 5)
		{
			line++;
			garo[y] = true;
		}
	}

	// 2. ����
	if (!sero[x])
	{
		for (r = 0; r < 5; r++)
			if (!my[r][x]) break;

		if (r == 5)
		{
			line++;
			sero[x] = true;
		}
	}

	// 3. �밢���� �ִ��� Ȯ��
	if (!dia[0] && x == y)
	{
		r = 4; c = 4;

		// 0, 0�� üũ�� �ؾ��ϹǷ� -1, -1����
		while (r != -1 && c != -1)
		{
			if (!my[r][c]) break;
			r--; c--;
		}
		if (r == -1 && c == -1)
		{
			line++;
			dia[0] = true;
		}
	}

	if (!dia[1] && x == (4 - y))
	{
		r = 4; c = 0;

		while (r != -1 && c != 5)
		{
			if (!my[r][c]) break;
			r--; c++;
		}
		if (r == -1 && c == 5)
		{
			line++;
			dia[1] = true;
		}
	}

	if (line >= 3) return 1;
	else           return 0;
}

int checkNumber2(int _num)
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (bingo[i][j] == _num)
			{
				my[i][j] = true;
				if (checkBingo2(j, i))
					return 1;
				return 0;
			}
		}
	}
	return 0;
}


int main() {

	//Please Enter Your Code Here
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			scanf("%d", &bingo[i][j]);

	for (int i = 0; i < 5; i++)
		memset(my[i], 0, sizeof(int) * 5);

	for (int i = 0; i < 25; i++)
	{
		int num;
		scanf("%d", &num);

		if (checkNumber2(num))
		{
			printf("%d", i + 1);
			return 0;
		}
	}

	return 0;
}