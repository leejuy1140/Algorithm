#include <stdio.h>
#include <string.h>

char arr[20];
bool check[10];
int n, flag, operation[2][2] = { {9, -1}, {0, 1} };

void showArr()
{
	for (int i = 0; i < 2 * n + 1; i += 2)
		printf("%d", arr[i]);
	printf("\n");
}

void inequal(int idx, int num, int op)
{
	if (flag) return;
	if (idx == 2 * n + 1) { showArr(); flag = 1; return; }

	if (arr[idx] != '<' && arr[idx] != '>')
	{
		if (check[num]) return;

		arr[idx] = num;
		check[num] = 1;
		inequal(idx + 1, num, op);
		check[num] = 0;
	}
	else
	{
		for (int i = operation[op][0], k = 0; k < 10; i += operation[op][1], k++)
		{
			if (check[i]) continue;
			if (arr[idx] == '<' && num > i) continue;
			if (arr[idx] == '>' && num < i) continue;

			inequal(idx + 1, i, op);
		}
		return;
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		getchar();
		scanf("%c", &arr[2 * i + 1]);
	}
	
	for (int op = 0; op < 2; op++)
	{
		flag = 0;
		for (int i = operation[op][0], k = 0; k < 10; i += operation[op][1], k++)
		{
			memset(check, 0, 10);
			inequal(0, i, op);
			if (flag) break;
		}
	}

	return 0;
}