#include <stdio.h>

const int MAX = 505;

int n, m, board[MAX][MAX];
int tetromino[19][4][2] = {
	{{1, 1}, {1, 2}, {1, 3}, {1, 4}}, // ��
	{{1, 1}, {2, 1}, {3, 1}, {4, 1}}, 
	{{1, 1}, {1, 2}, {2, 1}, {2, 2}}, // ��
	{{1, 1}, {1, 2}, {1, 3}, {2, 1}}, // ��
	{{1, 1}, {1, 2}, {1, 3}, {2, 3}},
	{{2, 1}, {2, 2}, {2, 3}, {1, 1}},
	{{2, 1}, {2, 2}, {2, 3}, {1, 3}},
	{{1, 1}, {2, 1}, {3, 1}, {1, 2}},
	{{1, 1}, {2, 1}, {3, 1}, {3, 2}},
	{{1, 2}, {2, 2}, {3, 2}, {1, 1}},
	{{1, 2}, {2, 2}, {3, 2}, {3, 1}},
	{{2, 1}, {2, 2}, {1, 1}, {3, 2}}, // ��
	{{2, 1}, {2, 2}, {1, 2}, {3, 1}},
	{{1, 2}, {2, 2}, {1, 1}, {2, 3}},
	{{1, 2}, {2, 2}, {1, 3}, {2, 1}},
	{{1, 1}, {1, 2}, {1, 3}, {2, 2}}, // ��
	{{2, 1}, {2, 2}, {2, 3}, {1, 2}},
	{{1, 1}, {2, 1}, {3, 1}, {2, 2}},
	{{1, 2}, {2, 2}, {3, 2}, {2, 1}}
};

int main()
{
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf("%d", &board[i][j]);

	int maxArea = 0;
	for (int i = 0; i < 19; i++)
	{
		int r = 1, c = 1;
		while (r <= n)
		{
			bool flag = 0;
			int curArea = 0;
			for (int j = 0; j < 4; j++)
			{
				int rr = r + tetromino[i][j][0] - 1;
				int cc = c + tetromino[i][j][1] - 1;
				if (cc > m || rr > n) { flag = 1; break; }
				curArea += board[rr][cc];
			}
			if (!flag && maxArea < curArea) maxArea = curArea;

			c++;
			if (flag || c > m) { r++; c = 1; }
		}
	}
	printf("%d\n", maxArea);

	return 0;
}