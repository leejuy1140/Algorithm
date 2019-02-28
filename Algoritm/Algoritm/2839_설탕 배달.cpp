#include <stdio.h>
const int MAX = 9999999;

int answer = MAX;
int bag[2] = { 5, 3 };

void solution(int weight, int idx, int cnt)
{
	if (idx >= 2) return;
	if (!weight) {
		answer = answer < cnt ? answer : cnt;
		return;
	}

	if (weight >= bag[idx]) // 넣을 수 있음.
	{
		solution(weight - bag[idx], idx, cnt + 1); // 넣음.
		solution(weight, idx + 1, cnt); // 안넣음.
	}
	else solution(weight, idx + 1, cnt);
}

int main()
{
	int n;	
	scanf("%d", &n);
	solution(n, 0, 0);
	if (answer == MAX)
	{
		if (n % bag[1] == 0) answer = n / bag[1];
		else				 answer = -1;
	}
	printf("%d", answer);
	return 0;
}