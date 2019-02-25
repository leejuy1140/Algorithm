#include <stdio.h>
#include <cmath>

const int MAX = 1000001;

int room[MAX];

int main()
{
	int n, leader, assistant;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &room[i]);
	scanf("%d %d", &leader, &assistant);

	long long answer = 0;
	for (int i = 0; i < n; i++)
	{
		room[i] -= leader;
		answer++;
		if (room[i] > 0)
			answer += ceil((float)room[i] / assistant);
	}
	printf("%lld\n", answer);

	return 0;
}