#include <stdio.h>
#include <string.h>

int n, cnt, cow[15];
char path[14], napkin[3] = { '+', '-', '.' };

/*
	인자로 path 인덱스와 napkin 인덱스를 주면,
	path 인덱스에 napkin 인덱스 속 값을 대입.
	탈출 조건 2: cnt 가 20 보다 크면 종료.
	탈출 조건 1: path 인덱스가 n-1 일 때,
				 계산 결과가 0 이면, 출력 & 카운팅 & 종료.

	오류 1: . 연속 2개 이상 처리
	오류 2: 9.10 = 910 인데 100 으로 처리
*/

void show()
{
	for (int i = 0; i < n; i++)
	{
		printf("%d ", cow[i]);
		if (i != n - 1)
			printf("%c ", path[i]);
	}
	printf("\n");
}

int calc()
{
	int tmp[15];
	memcpy(tmp, cow, sizeof(int) * n);

	for (int i = 0; i < n - 1; i++)
	{
		if (path[i] == '.')
		{
			if (!tmp[i])
			{
				int j = 0;
				while (!tmp[i - j]) j++;

				while (tmp[i + 1])
				{
					tmp[i - j] *= 10;
					tmp[i + 1] /= 10;
				}
				tmp[i - j] += cow[i + 1];
			}
			else
			{
				while (tmp[i + 1])
				{
					tmp[i] *= 10;
					tmp[i + 1] /= 10;
				}
				tmp[i] += cow[i + 1];
			}
			tmp[i + 1] = 0;
		}
	}

	int sum = tmp[0];
	for (int i = 0; i < n - 1; i++)
	{
		if (path[i] == '-') sum -= tmp[i + 1];
		else				sum += tmp[i + 1];
	}

	if (sum == 0) return 1;
	else		  return 0;
}

void dessert(int pi)
{
	if (pi == n - 1)
	{
		if (calc())
		{
			cnt++;
			if (cnt <= 20) show();
		}
		return;
	}

	for (int i = 0; i < 3; i++)
	{
		path[pi] = napkin[i];
		dessert(pi + 1);
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		cow[i] = i + 1;

	dessert(0);
	printf("%d\n", cnt);

	return 0;
}