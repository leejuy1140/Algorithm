#include <stdio.h>

int* func(int a, int* x);

int main()
{
	/*int nums[5] = { 11, 22, 33, 44, 55 };
	int* ptr = nums + 1;
	for (int i = 0; i < 4; i++)
		printf("%d ", *(ptr++));*/

	/*int arr[] = { 8, 5, 3, 1, 2, 7, 9 };
	int* p = arr + 2; // 3�� ����Ŵ.
	
	int a = *++p;	// 1�̸�, p�� 1�� ����Ŵ.
	int b = (*p)++; // ++�� �ڿ� �־ �ϴ� b���� 1 �� ��, 2�� ����� !!!
	printf("%d, %d\n", a, b); // 1, 1 ���.*/

	int a[100];
	for (int i = 0; i < 100; i++) a[i] = i * 10;

	int x = 10;
	int* p = func(x, a);
	printf("%d", x + a[0]+ a[1] + p[0] + p[1]); // 70

	return 0;
}

int* func(int a, int* x) // x�� a�� ���������� ����.
{
	a = a + 10;
	x = x + 1;
	*x = *x * 2;
	return x;
}