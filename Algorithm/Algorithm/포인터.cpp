#include <stdio.h>

int* func(int a, int* x);

int main()
{
	/*int nums[5] = { 11, 22, 33, 44, 55 };
	int* ptr = nums + 1;
	for (int i = 0; i < 4; i++)
		printf("%d ", *(ptr++));*/

	/*int arr[] = { 8, 5, 3, 1, 2, 7, 9 };
	int* p = arr + 2; // 3을 가리킴.
	
	int a = *++p;	// 1이며, p도 1을 가리킴.
	int b = (*p)++; // ++이 뒤에 있어서 일단 b에는 1 들어간 후, 2로 변경됨 !!!
	printf("%d, %d\n", a, b); // 1, 1 출력.*/

	int a[100];
	for (int i = 0; i < 100; i++) a[i] = i * 10;

	int x = 10;
	int* p = func(x, a);
	printf("%d", x + a[0]+ a[1] + p[0] + p[1]); // 70

	return 0;
}

int* func(int a, int* x) // x와 a는 개별적으로 존재.
{
	a = a + 10;
	x = x + 1;
	*x = *x * 2;
	return x;
}