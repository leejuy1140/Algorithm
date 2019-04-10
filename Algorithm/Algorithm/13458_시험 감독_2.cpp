#include <iostream>
#include <cmath>
using namespace std;

const int MAX = 1000001;

int n, student[MAX];

int main()
{
	int b, c;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &student[i]);
	scanf("%d %d", &b, &c);

	// 각 시험장마다 총 감독관 먼저 배치.
	long long answer = n;
	for (int i = 0; i < n; i++)
		student[i] -= b;

	// 부 감독관 배치하기.
	for (int i = 0; i < n; i++)
		if (student[i] > 0) answer += ceil((double)student[i] / c);
	printf("%lld", answer);

	return 0;
}