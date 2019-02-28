#include <stdio.h>
#include <algorithm>

const int DEAD = -1;
const int MAP_MAX = 15;
const int TREE_MAX = 1001;

int n, m, k;
int map[MAP_MAX][MAP_MAX];  // ���� ���� ���.
int food[MAP_MAX][MAP_MAX]; // �ܿ︶�� �߰��� ���.
int tree[MAP_MAX][MAP_MAX][TREE_MAX]; // ���� ���� ���� ����.
int dir[8][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1} };

/* ���̸�ŭ �ڽ� ĭ�� ����� �԰�, 1�� ����.
   ���̰� � ������ ����� �԰�, ����� �����ϸ� ����. */
void spring()
{
	for (int r = 1; r <= n; r++)
	{
		for (int c = 1; c <= n; c++)
		{
			if (tree[r][c][0]) // ���� ���� ������ ����.
			{
				// 1. � �������� ����� �Ա� ����, �������� ����.
				std::sort(&tree[r][c][1], &tree[r][c][1 + tree[r][c][0]]);

				// 2. ���������� ��� �Ա� ����.
				bool deadFlag = 0; // ��� �÷���.
				for (int k = 1; k <= tree[r][c][0]; k++)
				{
					if (map[r][c] >= tree[r][c][k]) // ��� ���.
					{
						map[r][c] -= tree[r][c][k];
						tree[r][c][k]++;
					}
					else
					{
						deadFlag = 1;
						tree[r][c][k] *= DEAD;
					}
				}
				if (deadFlag) tree[r][c][0] *= DEAD;
			}
		}
	}
}

/* ���� ���� ������ ����� ��. (���� ���� ���� / 2)��ŭ. */
void summer()
{
	for (int r = 1; r <= n; r++)
	{
		for (int c = 1; c <= n; c++)
		{
			if (tree[r][c][0] >= 0) continue;

			int deadCnt = 0;
			tree[r][c][0] *= DEAD;
			for (int k = 1; k <= tree[r][c][0]; k++)
			{
				if (tree[r][c][k] < 0)
				{
					int age = tree[r][c][k] * DEAD;
					deadCnt++;
					tree[r][c][k] = 0;
					map[r][c] += (age / 2);
				}
			}
			tree[r][c][0] -= deadCnt;
		}
	}
}

/* ���� ���̰� 5����� ������ 8��������, ���� 1�� ���� �߰�. */
void autumn()
{
	for (int r = 1; r <= n; r++)
	{
		for (int c = 1; c <= n; c++)
		{
			if (!tree[r][c][0]) continue;
			for (int k = 1; k <= tree[r][c][0]; k++)
			{
				if (tree[r][c][k] % 5 == 0)
				{
					for (int i = 0; i < 8; i++)
					{
						int nr = r + dir[i][0];
						int nc = c + dir[i][1];
						if (nr < 1 || nc < 1 || nr > n || nc > n) continue;

						tree[nr][nc][0]++;
						tree[nr][nc][tree[nr][nc][0]] = 1;
					}
				}
			}
		}
	}
}

/* �κ��� food��ŭ �� ĭ�� ��� �߰�. */
void winter()
{
	for (int r = 1; r <= n; r++)
		for (int c = 1; c <= n; c++)
			map[r][c] += food[r][c];
}

int main()
{
	scanf("%d %d %d", &n, &m, &k);
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			map[i][j] = 5; // �ʱ� ���: 5
			scanf("%d", &food[i][j]);
		}
	}
	for (int i = 0; i < m; i++)
	{
		int x, y, z;
		scanf("%d %d %d", &x, &y, &z);
		tree[x][y][0] = 1;
		tree[x][y][1] = z;
	}

	while (k--)
	{
		spring();
		summer();
		autumn();
		winter();
	}

	int treeNum = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			treeNum += tree[i][j][0];
	printf("%d\n", treeNum);

	return 0;
}