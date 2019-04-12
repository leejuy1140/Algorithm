#include <stdio.h>
#include <string.h> // 배열 초기화.
#include <queue>	// bfs
using namespace std;

const int MAX = 51;

queue<pair<int, int>> q;
int together[MAX][MAX];	   // 연합인 나라들을 숫자로 표시.
bool visited[MAX][MAX];	   // bfs 중복 방지.
int population[MAX * MAX]; // 해당 연합국의 인구이동후 인구수 저장.

int n, L, R, map[MAX][MAX];
int dir[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

int inline MyAbs(int num) {
	return num < 0 ? -num : num;
}

/* (r, c) 나라에서 시작하여, 연합인 나라를 num으로 표시. 
   만약 현재 나라와 연합인 나라가 없다면, 거짓 반환.	 */
int Move(int r, int c, int unionNum)
{
	memset(visited, false, sizeof(visited));

	q.push({ r, c });
	visited[r][c] = true;
	together[r][c] = unionNum;

	int totalCnt = 1;
	int totalPop = map[r][c];
	while (!q.empty())
	{
		int cur_r = q.front().first;
		int cur_c = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			int next_r = cur_r + dir[i][0];
			int next_c = cur_c + dir[i][1];
			if (next_r < 0 || next_c < 0 || next_r >= n || next_c >= n) continue;
			if (visited[next_r][next_c] || together[next_r][next_c]) continue;
			// 방문했던 국가나 이미 연합인 국가 패스. (나랑 연합일리가 없음.)

			int diff = MyAbs(map[cur_r][cur_c] - map[next_r][next_c]);
			if (diff >= L && diff <= R) // 연합 조건이 성립하면, 큐에 삽입.
			{
				totalCnt++;
				totalPop += map[next_r][next_c];
				
				q.push({ next_r, next_c });
				visited[next_r][next_c] = true;
				together[next_r][next_c] = unionNum;
			}
		}
	}
	
	// 현재 정보 저장 및 인구 이동 여부 반환.
	population[unionNum] = totalPop / totalCnt;
	if (totalCnt > 1) return 1;
	else		      return 0;
}

int main()
{
	scanf("%d %d %d", &n, &L, &R);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			scanf("%d", &map[i][j]);

	int answer = 0;
	while (1)
	{
		// 1. 연합 배열 및 정보 벡터 초기화.
		memset(together, 0, sizeof(together));

		// 2. 연합인 나라 확인하기.
		int unionNum = 1; // 연합 번호
		int unionCnt = 0; // 연합 수
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (!together[i][j]) // 연합 없으면, 구함.
					unionCnt += Move(i, j, unionNum++);
			}
		}

		// 3. 연합국이 없다면, 탈출.
		if (!unionCnt) break;
		
		// 4. 인구 이동 시작.
		answer++;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
				map[i][j] = population[together[i][j]];
		}
	}
	printf("%d", answer);

	return 0;
}
