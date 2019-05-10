/*
21:46 시작.
00:00 종료.
00시간 00분 소요.

1) 문제 이해
- R 연산: 행 정렬 수행. (행 개수 >= 열 개수)
- C 연산: 열 정렬 수행. (행 개수 < 열 개수)
- 정렬 방법
  각각의 숫자의 등장 횟수 오름차순.
  등장 횟수가 같으면 숫자 오름차순.
  정렬 후 배열에 숫자와 등장 횟수 순으로 삽입.
- 정렬 후
  R 연산 후 행의 크기가 가장 큰 행을 기준으로 모든 행의 크기 증가.
  C 연산 후 행의 크기가 가장 큰 열을 기준으로 모든 열의 크기 증가.
  빈 곳은 0으로 패딩. (정렬 시 0은 무시.)
- 행 또는 열의 크기가 100을 넘어가면, 처음 100개만 사용.
- A[r][c] == k를 만족하는 최소 연산 시간 출력. (100 초과 시 -1 출력.)
2) 변수
const int MAX = 101;
const int INF = 999999;
int rSize, cSize; // 행과 열의 크기.
struct MyA { int num, cnt; } myA[MAX]; 
3) 설계
1. 행과 열의 크기 비교 후 각각의 연산 함수 호출.
 2. 하나의 행 또는 열의 숫자 당 개수를 myA 배열에 카운팅.
 3. myA 배열 오름차순 정렬.
 4. 정렬 후 값을 조건에 맞춰 A 배열에 넣음.
 5. A의 최대 크기 확인 후 갱신.
 6. 모든 행 또는 열에 대해 정렬을 수행한 후 최대 크기에 맞춰 0 패딩.
7. A[r][c]가 k면 정답 출력.
4) 경우의 수
5) 초기화 필요한 변수
myA[i].num = i;   // 정렬 후에도 숫자를 찾을 수 있도록.
myA[i].cnt = INF;
6) 가지치기
*/

#include <iostream>
#include <algorithm>
using namespace std;

const int MAX = 105;
const int INF = 999999;

int rSize, cSize; // 행과 열의 크기.
int r, c, k, A[MAX][MAX];
struct MyA { int num, cnt; } myA[MAX];

bool compare(MyA& a, MyA& b)
{
	if (a.cnt > b.cnt) return false;
	else if (a.cnt == b.cnt)
	{
		if (a.num > b.num) return false;
		else			   return true;
	}
	else return true;
}

void Do_R_Operation()
{
	int newSize = 0;
	for (int i = 0; i < rSize; i++)
	{
		// 2. 하나의 행 또는 열의 숫자 당 개수를 myA 배열에 카운팅.
		for (int j = 0; j < cSize; j++)
		{
			if (A[i][j] == 0) continue;

			if (myA[A[i][j]].cnt == INF)
			{
				myA[A[i][j]].num = A[i][j];
				myA[A[i][j]].cnt = 1;
			}
			else myA[A[i][j]].cnt++;
		}

		// 3. myA 배열 오름차순 정렬.
		sort(&myA[0], &myA[MAX], compare);

		// 4. 정렬 후 값을 조건에 맞춰 A 배열에 넣음.
		int A_idx = 0;
		for (int j = 0; j < MAX; j++)
		{
			if (A_idx > 100 || myA[j].cnt == INF) break;

			A[i][A_idx++] = myA[j].num;
			A[i][A_idx++] = myA[j].cnt;
			myA[j].cnt = INF;
		}
		A[i][A_idx] = -1;

		// 5. A의 최대 크기 확인 후 갱신.
		if (newSize < A_idx) newSize = A_idx;
	}

	// 6. 최대 크기에 맞춰 0 패딩.
	for (int i = 0; i < rSize; i++)
	{
		for (int j = newSize; j >= 0; j--)
		{
			if (A[i][j] == -1)
			{
				A[i][j] = 0;
				break;
			}
			A[i][j] = 0;
		}
	}
	
	rSize = newSize;
	return;
}

void Do_C_Operation()
{
	int newSize = 0;
	for (int i = 0; i < cSize; i++)
	{
		// 2. 하나의 행 또는 열의 숫자 당 개수를 myA 배열에 카운팅.
		for (int j = 0; j < rSize; j++)
		{
			if (A[j][i] == 0) continue;

			if (myA[A[j][i]].cnt == INF)
			{
				myA[A[j][i]].num = A[j][i];
				myA[A[j][i]].cnt = 1;
			}
			else myA[A[j][i]].cnt++;
		}

		// 3. myA 배열 오름차순 정렬.
		sort(&myA[0], &myA[MAX], compare);

		// 4. 정렬 후 값을 조건에 맞춰 A 배열에 넣음.
		int A_idx = 0;
		for (int j = 0; j < MAX; j++)
		{
			if (A_idx > 100 || myA[j].cnt == INF) break;

			A[A_idx++][i] = myA[j].num;
			A[A_idx++][i] = myA[j].cnt;
			myA[j].cnt = INF;
		}
		A[A_idx][i] = -1;

		// 5. A의 최대 크기 확인 후 갱신.
		if (newSize < A_idx) newSize = A_idx;
	}

	// 6. 최대 크기에 맞춰 0 패딩.
	for (int i = 0; i < cSize; i++)
	{
		for (int j = newSize; j >= 0; j--)
		{
			if (A[j][i] == -1)
			{
				A[j][i] = 0;
				break;
			}
			A[j][i] = 0;
		}
	}

	cSize = newSize;
	return;
}

int main()
{
	rSize = cSize = 3;
	for (int i = 0; i < MAX; i++)
	{
		myA[i].num = i;
		myA[i].cnt = INF;
	}

	scanf("%d %d %d", &r, &c, &k);
	for (int i = 0; i < rSize; i++)
		for (int j = 0; j < cSize; j++)
			scanf("%d", &A[i][j]);

	int time = 0;
	while(A[r - 1][c - 1] != k)
	{ 
		// 1. 행과 열의 크기 비교 후 각각의 연산 함수 호출.
		if (rSize >= cSize) Do_R_Operation();
		else				Do_C_Operation();

		/*printf("\n");
		for (int i = 0; i < rSize; i++)
		{
			for (int j = 0; j < cSize; j++)
				printf("%d ", A[i][j]);
			printf("\n");
		}*/

		time++;
		if (time > 100)
		{
			time = -1;
			break;
		}
	}
	printf("%d\n", time);

	return 0;
}