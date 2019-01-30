#include <stdio.h>
#include <queue>
using namespace std;

const int MAX = 100001;

int n, k;
bool visited[MAX];

int bfs(int start)
{
	queue<int> q;
	q.push(start);
	visited[start] = 1;

	int cnt = 0;
	while (!q.empty())
	{
		int cur = q.front();
		q.pop();

		for (int i = 0; i < 2; i++)
		{
			int next;
			if(!i) next = cur * 2;
			else   next = cur / 3;

			if (next <= n && !visited[next])
			{
				cnt++;
				q.push(next);
				visited[next] = 1;
			}
		}
	}
	return cnt;
}


int main()
{
	scanf("%d %d", &n, &k);
	
	int sick = bfs(k);
	printf("%d", n - sick);
	
	return 0;
}