#include <stdio.h>
#include <string.h>

int n, cnt, cow[15];
char path[14], napkin[3] = { '+', '-', '.' };

/*
	���ڷ� path �ε����� napkin �ε����� �ָ�,
	path �ε����� napkin �ε��� �� ���� ����.
	Ż�� ���� 2: cnt �� 20 ���� ũ�� ����.
	Ż�� ���� 1: path �ε����� n-1 �� ��,
				 ��� ����� 0 �̸�, ��� & ī���� & ����.

	���� 1: . ���� 2�� �̻� ó��
	���� 2: 9.10 = 910 �ε� 100 ���� ó��
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