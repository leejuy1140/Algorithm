#include <stdio.h>
#include <algorithm>
#define MAX 1001

int main()
{
	int n, data[MAX];
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &data[i]);

	int turn = 0;
	int s = 0, e = n - 1;
	int subin = 0, sunwoong = 0;

	while (s <= e)
	{
		turn++;

		if (e - s + 1 <= 3)
		{
			if (data[s] > data[e])
			{
				if (turn % 2) subin += data[s];
				else         sunwoong += data[s];
				s++;
			}
			else
			{
				if (turn % 2) subin += data[e];
				else         sunwoong += data[e];
				e--;
			}
		}
		else
		{
			if (data[s + 2] > data[e - 2])
			{
				if (turn % 2) subin += data[s];
				else         sunwoong += data[s];
				s++;
			}
			else
			{
				if (turn % 2) subin += data[e];
				else         sunwoong += data[e];
				e--;
			}
		}
	}
	printf("%d %d\n", subin, sunwoong);

	return 0;
}