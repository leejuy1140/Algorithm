#include <stdio.h>

int n, r, c, full, half;

/* 현재 (r, c)가 어느 사분면인지 반환. */
int GetPlane()
{
	if (r < half && c < half) return 1;
	if (r < half && c >= half) return 2;
	if (r >= half && c < half) return 3;
	return 4;
}

int main()
{
	scanf("%d %d %d", &n, &r, &c);

	full = 1;
	for (int i = 0; i < n; i++) full *= 2;
	half = full / 2;
	
	int num = 0;
	while (half)
	{
		int plane = GetPlane();
		num += (half * half) * (plane - 1);
		if(r >= half) r -= half;
		if(c >= half) c -= half;
		full = half;
		half = full / 2;
	}
	printf("%d\n", num);

	return 0;
}