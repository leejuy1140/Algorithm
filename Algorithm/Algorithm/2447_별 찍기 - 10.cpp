/*
17:08 시작
18:34 종료.
1시간 26분 소요.
(규칙 찾는게 어려웠음..)

1) 문제 이해
   가로, 세로 3등분 후 그 중앙은 항상 빈 칸.
   ***
   * *
   *** -> 모양의 형태가 계속 반복되는 꼴.
2) 변수
   1. 한 줄 씩 차례로 출력하는 것이 아니기 때문에, 배열 사용.
3) 설계
   점점 작은 기본꼴의 형태로, 분할 정복으로 해결.
   solution(int size, int x, int y)
   1. (x, y)부터 현재 크기만큼의 구멍을 뚫어주는 함수.
   2. 현재 크기의 구멍을 뚫었으면, 현재 크기의 구멍을 갖는 다음 위치로 이동.
   3. 다음 위치가 범위를 벗어난다면, 다 뚫은 것이므로 크기를 1/3로 줄인 후 반복.
4) 경우의 수
5) 초기화 필요한 변수
6) 가지치기
   1. 구멍의 위치가 범위를 벗어남.
   2. 구멍의 크기가 1보다 작음.
   3. 이미 구멍이 뚫려있음.
*/

#include <stdio.h>

const int MAX = 2200; // 입력 범위는 3^7까지

int N;
bool map[MAX][MAX]; // 빈칸이면, true

/* (x, y)에서부터 size만큼의 정사각형 구멍을 뚫는 함수. */
void solution(int size, int x, int y)
{
	if (size < 1 || x + size > N || y + size > N) return;
	if (map[x][y]) return; // 이미 구멍이 뚫려있으면, 패스.
	
	// 현재 size만큼 구멍을 뚫고
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			map[x + i][y + j] = true;

	// 현재 size의 구멍을 갖는 다음 위치 찾기.
	solution(size, x + 3 * size, y);
	solution(size, x, y + 3 * size);

	// 현재 size의 1/3만큼의 구멍을 뚫으려 출발.
	solution(size / 3, x / 3, y / 3);
}

int main()
{
	scanf("%d", &N);
	solution(N / 3, N / 3, N / 3);
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (map[i][j]) printf(" ");
			else		   printf("*");
		}
		printf("\n");
	}
	return 0;
}