#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;


int A[8], a[8], N;
bool visited[8];

int calculate()
{
	int num = 0;
	for (int i = 0; i < N - 1; i++)
		num += abs(a[i] - a[i + 1]);
	return num;
}

int solution(int a_idx, int A_idx)
{
	a[a_idx] = A[A_idx];

	// 재귀함수 탈출조건: 배열을 다 채웠으면 공식 계산
	if (a_idx == N - 1) return calculate();

	int result = -1;
	for (int j = 0; j < N; j++)
	{
		if (!visited[j])
		{
			visited[j] = true;
			result = max(result, solution(a_idx + 1, j));
			visited[j] = false;
		}
	}
	return result;
}

int main()
{
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d", &A[i]);

	int maximum = -1;
	for (int i = 0; i < N; i++)
	{
		memset(a, -1, sizeof(int)*N);
		memset(visited, false, sizeof(bool)*N);
		visited[i] = true;
		maximum = max(maximum, solution(0, i));
	}
	printf("%d\n", maximum);

	return 0;
}