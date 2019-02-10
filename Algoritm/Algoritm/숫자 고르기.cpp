#include <stdio.h>
#include <string.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int n;
vector<int> table;
vector<char> visited;

void dfs(queue<int> &set, int num)
{
	/* 방문했던 숫자를 만나면,
	   경로의 맨 앞부터 같은 숫자가 나올 때까지 pop */
	if (visited[num])
	{
		while (!set.empty())
		{
			if (set.front() == num) break;
			set.pop();
		}
		return;
	}

	visited[num] = 1;
	set.push(num);

	dfs(set, table[num]);
}

int main()
{
	scanf("%d", &n);
	table.resize(n + 1);
	visited.resize(n + 1);
	for (int i = 1; i <= n; i++)
		scanf("%d", &table[i]);
	
	vector<int> answerSet;		// 정답 집합
	vector<char> choosed(n, 0); // 이미 선택된 수 체크
	
	for (int i = 1; i <= n; i++)
	{
			memset(&visited[0], 0, n + 1);
			queue<int> curSet;
			dfs(curSet, i);

			/* 부분 집합 중 이미 정답 처리된 숫자를 제외하고, push_back */
			while (!curSet.empty())
			{
				int curNum = curSet.front();
				curSet.pop();
				if (choosed[curNum]) continue;

				answerSet.push_back(curNum);
				choosed[curNum] = 1;
			}
	}

	printf("%d\n", answerSet.size());
	sort(answerSet.begin(), answerSet.end());
	for (int i = 0; i < answerSet.size(); i++)
		printf("%d\n", answerSet[i]);
	
	return 0;
}