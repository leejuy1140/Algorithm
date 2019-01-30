#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 1000;

char num1[MAX], num2[MAX];
int *result, resultSize;

void multiply() // O(n^2)
{
	result = (int *)malloc(sizeof(int) * resultSize);
	memset(result, 0, sizeof(int) * resultSize);

	for (int i = 0; i < strlen(num1); i++)
	{
		// ���� ������ ���� �ʾƵ� ��
		for (int j = 0; j < strlen(num2); j++)
			result[i + j] += (num1[i] - '0') * (num2[j] - '0');
	}
}

void normalization()
{
	for (int i = 0; i < resultSize; i++) // O(n)
	{
		result[i + 1] += result[i] / 10;
		result[i] %= 10;
	}
}

int main()
{
	scanf("%s %s", num1, num2);
	resultSize = strlen(num1) + strlen(num2) + 2;

	// �ø� ó���� �迭���� �����ϰ� �ϱ� ���� ���ڿ� ������
	reverse(num1, num1 + strlen(num1));
	reverse(num2, num2 + strlen(num2));

	// ���� ó��
	multiply();

	// �ø� ó��
	normalization();

	int flag = 0;
	for (int i = resultSize - 1; i >= 0; i--)
	{
		if (!flag && !result[i]) continue;
		printf("%d", result[i]);
	}

	return 0;
}