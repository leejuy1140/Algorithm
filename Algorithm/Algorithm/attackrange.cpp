#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int stat;
int n, r, **map;
int direction[4][2] = { {-1, 0}, {0, -1}, {1, 0}, {0, 1} }; // (x, y) �»���� 

void showMap(int _x, int _y)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i == _y - 1 && j == _x - 1)
				printf("x ");
			else
				printf("%d ", map[i][j]);
		}
		printf("\n");
	}
}

int oneWay(int *_cur_x, int *_cur_y, int _dir)
{
	int d; // ��迡�� �ɸ��� 1, �ƴϸ� 0 ��ȯ
	int prev_dir = (_dir + 2) % 4;

	for (d = 1; d <= r; d++)
	{
		*_cur_x += direction[_dir][0];
		*_cur_y += direction[_dir][1];

		if (*_cur_x < 0 || *_cur_y < 0 || *_cur_x >= n || *_cur_y >= n)
		{
			*_cur_x += direction[prev_dir][0];
			*_cur_y += direction[prev_dir][1];

			stat = 1;
			d--;
			break;
		}

		map[*_cur_y][*_cur_x] = d;
	}

	return d - 1;
}

void otherWay(int _prev_x, int _prev_y, int _start_d, int _dir)
{
	int new_dir = (_dir + 1) % 4;
	int prev_dir = (_dir + 2) % 4;

	for (int d = _start_d; d > 0; d--)
	{
		// ��迡�� �ɸ� ���̸� ���� ĭ���� �̵� ����
		// ó������ ����
		if (stat) stat = 0;

		else // ���� ĭ���� �̵�
		{
			_prev_x += direction[prev_dir][0];
			_prev_y += direction[prev_dir][1];
		}

		int new_x = _prev_x;
		int new_y = _prev_y;

		// ���ο� �������� �̵�
		for (int cur_d = d; cur_d <= r; cur_d++)
		{
			new_x += direction[new_dir][0];
			new_y += direction[new_dir][1];

			if (new_x < 0 || new_y < 0 || new_x >= n || new_y >= n)
				break;

			map[new_y][new_x] = cur_d;
		}
	}
}

int main() {

	//Please Enter Your Code Here
	scanf("%d", &n);

	int x, y;
	scanf("%d %d %d", &y, &x, &r);

	map = (int **)malloc(sizeof(int *) * n);
	for (int i = 0; i < n; i++)
	{
		map[i] = (int *)malloc(sizeof(int) * n);
		memset(map[i], 0, sizeof(int) * n);
	}

	// �������� 4���� ����
	for (int dir = 0; dir < 4; dir++)
	{
		int cur_x = x - 1;
		int cur_y = y - 1;

		// �� ����(��������)���� �����Ÿ� ǥ��
		int start_d = oneWay(&cur_x, &cur_y, dir);

		// �� �� �����Ÿ� ǥ��
		if (stat) start_d += 2;
		otherWay(cur_x, cur_y, start_d, dir);
	}

	showMap(x, y);

	return 0;
}