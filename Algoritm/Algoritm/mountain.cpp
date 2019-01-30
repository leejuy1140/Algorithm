#include <stdio.h>

void fractal(int _n)
{
	if (_n == 1)
	{
		printf("1");
		return;
	}

	fractal(_n - 1);
	printf("%d", _n);
	fractal(_n - 1);
}

int main()
{
	int n;
	scanf("%d", &n);

	fractal(n);

	return 0;
}