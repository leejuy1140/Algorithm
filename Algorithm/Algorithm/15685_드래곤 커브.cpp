#include <iostream>
#include <vector>
using namespace std;

int N; // 드래곤 커브 개수
int map[101][101]; // 100 * 100 격자

int main()
{
	scanf("%d", &N);
	for (int i = 0; i < N; i++) // 드래곤 커브 하나씩 그림
	{
		int x, y, d, g; // 시작 점, 방향, 세대
		scanf("%d %d %d %d", &x, &y, &d, &g);

		vector<int> dragon_x; // 드래곤 커브 위치
		vector<int> dragon_y;
		dragon_x.push_back(x);
		dragon_y.push_back(y);
		map[y][x] = 1; // 시작 점 격자에 표시

		int last_x, last_y; // 끝 점 표시
		if (d == 0) { last_x = x + 1; last_y = y; } // x+1
		if (d == 1) { last_x = x; last_y = y - 1; } // y-1
		if (d == 2) { last_x = x - 1; last_y = y; } // x-1
		if (d == 3) { last_x = x; last_y = y + 1; } // y+1
		dragon_x.push_back(last_x);
		dragon_y.push_back(last_y);
		map[last_y][last_x] = 1;

		while (g--) // 드래곤 세대 표시
		{
			int num = dragon_x.size(); // 이전 세대의 드래곤 커브 수
			last_x = dragon_x.back();
			last_y = dragon_y.back();

			// 현재 세대의 드래곤 커브 구하기 (끝 점: num - 1)
			for (int i = num - 2; i >= 0; i--)
			{
				int new_x = last_x + (dragon_y[i] - last_y) * -1; // 회전 변환
				int new_y = last_y + (dragon_x[i] - last_x) * 1;
				dragon_x.push_back(new_x);
				dragon_y.push_back(new_y);
				map[new_y][new_x] = 1;
			}
		}
	}

	int cnt = 0; // 격자의 네 모서리에 드래곤 커브가 포함된 수
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			// 격자의 네 모서리에 드래곤 커브가 포함되면,
			if (map[i][j] && map[i][j + 1] && map[i + 1][j] && map[i + 1][j + 1])
				cnt++;
		}
	}
	printf("%d\n", cnt);

	return 0;
}