#include <stdio.h>
#include <string.h>

const int MAX = 100001;

// visited[i][0]: ���� �ñ����� Ȯ���ϱ� ����
// visited[i][1]: dfs�ϸ鼭 ������ ��带 ī���� �ϱ� ����
int wishList[MAX], visited[MAX][2], curMemCnt;

void dfs(int student, int numOfMem, int teamNo)
{
	visited[student][0] = teamNo;
	visited[student][1] = numOfMem;

	int partner = wishList[student];
	if (!visited[partner][0])
		dfs(partner, numOfMem + 1, teamNo);
	else if (visited[partner][0] == teamNo) // ���� �ñ⿡ �湮�ߴ� ���� �ǵ��ư���
		curMemCnt += numOfMem - visited[partner][1] + 1; // ���� �� ���
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