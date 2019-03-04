#include <stdio.h>
#include <algorithm>
using namespace std;

const int MAX = 9;

int height[MAX];
bool selected[MAX], flag;

void SelectDwarf(int idx, int cnt)
{
	if (flag) return;
	
	selected[idx] = true;
	
	if (cnt == 7)
	{
		int sum = 0;
		for (int i = 0; i < MAX; i++)
			if (selected[i]) sum += height[i];
		
		if (sum == 100) // 일곱 난쟁이 키 합이 100이면, 끝.
		{
			for (int i = 0; i < MAX; i++)
				if (selected[i]) printf("%d\n", height[i]);
			flag = true;
		}
		return;
	}

	for (int i = idx + 1; i < MAX; i++)
	{
		if (!selected[i])
		{
			SelectDwarf(i, cnt + 1);
			selected[i] = 0;
		}
	}
}

int main()
{
	for (int i = 0; i < MAX; i++)
		scanf("%d", &height[i]);
	sort(&height[0], &height[MAX]);

	for (int i = 0; i < MAX; i++)
	{
		if (!selected[i]) // 선택 안 된 난쟁이 선택.
		{
			SelectDwarf(i, 1);
			selected[i] = 0;
		}
	}
	return 0;
}