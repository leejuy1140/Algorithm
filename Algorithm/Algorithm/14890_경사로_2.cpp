#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAX = 105;

bool slope[MAX][MAX];
int n, l, map[MAX][MAX];

int main()
{
	scanf("%d %d", &n, &l);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			scanf("%d", &map[i][j]);

	int answer = 0;
	for (int i = 1; i <= n; i++) // ���� üũ.
	{
		bool flag = true; // �� ������ ����.
		for (int j = 1; j < n; j++)
		{
			int curRow = map[i][j];
			int nextRow = map[i][j + 1];

			// 1. �������� 1���� Ŀ�� ���� ��ġ �Ұ�.
			if (abs(map[i][j] - map[i][j + 1]) > 1)
			{
				flag = false;
				break;
			}
			if (abs(map[i][j] - map[i][j + 1]) == 1)
			{
				// 2. ������ �� ����, ���� ��ġ �������� üũ.
				if (map[i][j] > map[i][j + 1])
				{
					if (j + l > n)
					{
						flag = false;
						break;
					}

					int h = map[i][j + 1];
					for (int k = j + 1; k <= j + l; k++)
					{
						if (h != map[i][k] || slope[i][k])
						{
							flag = false;
							break;
						}
					}

					if (flag)
					{
						for (int k = j + 1; k <= j + l; k++)
							slope[i][k] = true;
						j += l - 1;
					}
				}
				// 3. �������� �� ����, ���� ��ġ �������� üũ.
				else
				{
					if (j - l + 1 < 1)
					{
						flag = false;
						break;
					}

					int h = map[i][j];
					for (int k = j; k >= j - l + 1; k--)
					{
						if (h != map[i][k] || slope[i][k])
						{
							flag = false;
							break;
						}
					}

					if (flag)
					{
						for (int k = j; k >= j - l + 1; k--)
							slope[i][k] = true;
					}
				}
			}
		}
		if (flag) answer++;
	}
	memset(slope, false, sizeof(slope));

	for (int i = 1; i <= n; i++) // ���� üũ.
	{
		bool flag = true; // �� ������ ����.
		for (int j = 1; j < n; j++)
		{
			// 1. �������� 1���� Ŀ�� ���� ��ġ �Ұ�.
			if (abs(map[j][i] - map[j + 1][i]) > 1)
			{
				flag = false;
				break;
			}
			if (abs(map[j][i] - map[j + 1][i]) == 1)
			{
				// 2. ���� �� ����, ���� ��ġ �������� üũ.
				if (map[j][i] > map[j + 1][i])
				{
					if (j + l > n)
					{
						flag = false;
						break;
					}

					int h = map[j + 1][i];
					for (int k = j + 1; k <= j + l; k++)
					{
						if (h != map[k][i] || slope[k][i])
						{
							flag = false;
							break;
						}
					}

					if (flag)
					{
						for (int k = j + 1; k <= j + l; k++)
							slope[k][i] = true;
						j += l - 1;
					}
				}
				// 3. �Ʒ��� �� ����, ���� ��ġ �������� üũ.
				else
				{
					if (j - l + 1 < 1)
					{
						flag = false;
						break;
					}

					int h = map[j][i];
					for (int k = j; k >= j - l + 1; k--)
					{
						if (h != map[k][i] || slope[k][i])
						{
							flag = false;
							break;
						}
					}

					if (flag)
					{
						for (int k = j; k >= j - l + 1; k--)
							slope[k][i] = true;
					}
				}
			}
		}
		if (flag) answer++;
	}
	printf("%d", answer);
	return 0;
}