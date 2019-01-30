#include <stdio.h>

const int MAX = 101;
const int QUOTIENT = 1000007;

int main()
{
	int n, fibo[MAX];
	scanf("%d", &n);

/*
	2*4�� ���簢���� ä��� ����� �����,
	������ ĭ�� 1*2 �� �ϳ��� ���� ��, 2*1 �� �ΰ��� �������� ���� �� ����.
	����, ������ ĭ�� ä��� ���� ĭ�� 2*3�� 2*2�� ä��� ����� ���� ���� ���� ����. 
	�̴� �Ǻ���ġ ������ ����.
*/

	fibo[0] = fibo[1] = 1;
	for (int i = 2; i <= n; i++)
	{
		fibo[i] = fibo[i - 1] + fibo[i - 2];
		if (fibo[i] > QUOTIENT) fibo[i] %= QUOTIENT;
	}
	printf("%d", fibo[n]);

	return 0;
}