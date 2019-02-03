#include <stdio.h>
#include <string.h>

const int MAX = 100001;

// visited[i][0]: 같은 시기인지 확인하기 위해
// visited[i][1]: dfs하면서 인접한 노드를 카운팅 하기 위해
int wishList[MAX], visited[MAX][2], curMemCnt;

void dfs(int student, int numOfMem, int teamNo)
{
	visited[student][0] = teamNo;
	visited[student][1] = numOfMem;

	int partner = wishList[student];
	if (!visited[partner][0])
		dfs(partner, numOfMem + 1, teamNo);
	else if (visited[partner][0] == teamNo) // 같은 시기에 방문했던 노드로 되돌아가면
		curMemCnt += numOfMem - visited[partner][1] + 1; // 팀원 수 계산
}

int main()
{
	int t; scanf("%d", &t);
	while (t--)
	{
		int n; scanf("%d", &n);
		for (int i = 1; i <= n; i++)
		{
			scanf("%d", &wishList[i]);
			visited[i][0] = visited[i][1] = 0;
		}

		curMemCnt = 0;
		int teamNo = 1;
		for (int i = 1; i <= n; i++)
		{
			if (!visited[i][0])
				dfs(i, 1, teamNo++);
		}
		printf("%d\n", n - curMemCnt);
	}
	return 0;
}