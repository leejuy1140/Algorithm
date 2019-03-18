#include <iostream>
#include <vector>
using namespace std;

int N; // �巡�� Ŀ�� ����
int map[101][101]; // 100 * 100 ����

int main()
{
	scanf("%d", &N);
	for (int i = 0; i < N; i++) // �巡�� Ŀ�� �ϳ��� �׸�
	{
		int x, y, d, g; // ���� ��, ����, ����
		scanf("%d %d %d %d", &x, &y, &d, &g);

		vector<int> dragon_x; // �巡�� Ŀ�� ��ġ
		vector<int> dragon_y;
		dragon_x.push_back(x);
		dragon_y.push_back(y);
		map[y][x] = 1; // ���� �� ���ڿ� ǥ��

		int last_x, last_y; // �� �� ǥ��
		if (d == 0) { last_x = x + 1; last_y = y; } // x+1
		if (d == 1) { last_x = x; last_y = y - 1; } // y-1
		if (d == 2) { last_x = x - 1; last_y = y; } // x-1
		if (d == 3) { last_x = x; last_y = y + 1; } // y+1
		dragon_x.push_back(last_x);
		dragon_y.push_back(last_y);
		map[last_y][last_x] = 1;

		while (g--) // �巡�� ���� ǥ��
		{
			int num = dragon_x.size(); // ���� ������ �巡�� Ŀ�� ��
			last_x = dragon_x.back();
			last_y = dragon_y.back();

			// ���� ������ �巡�� Ŀ�� ���ϱ� (�� ��: num - 1)
			for (int i = num - 2; i >= 0; i--)
			{
				int new_x = last_x + (dragon_y[i] - last_y) * -1; // ȸ�� ��ȯ
				int new_y = last_y + (dragon_x[i] - last_x) * 1;
				dragon_x.push_back(new_x);
				dragon_y.push_back(new_y);
				map[new_y][new_x] = 1;
			}
		}
	}

	int cnt = 0; // ������ �� �𼭸��� �巡�� Ŀ�갡 ���Ե� ��
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			// ������ �� �𼭸��� �巡�� Ŀ�갡 ���ԵǸ�,
			if (map[i][j] && map[i][j + 1] && map[i + 1][j] && map[i + 1][j + 1])
				cnt++;
		}
	}
	printf("%d\n", cnt);

	return 0;
}