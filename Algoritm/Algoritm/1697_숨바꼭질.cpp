#include <stdio.h>
#include <queue>
using namespace std;

const int MAX = 200001; // 넘어갈수도 있음 !

int n, k, visited[MAX]; // cnt

int bfs()
{
	queue<int> q;
	q.push(n);
	visited[n] = 1;

	while (!q.empty())
	{
		int cur = q.front();
		q.pop();
		if (cur == k) return visited[k] - 1;

		if (cur + 1 < MAX)
		{
			if (!visited[cur + 1])
			{
				visited[cur + 1] = visited[cur] + 1;
				q.push(cur + 1);
			}
		}
		if (cur - 1 >= 0)
		{
			if (!visited[cur - 1])
			{
				visited[cur - 1] = visited[cur] + 1;
				q.push(cur - 1);
			}
		}
		if (cur * 2 < MAX)
		{
			if (!visited[cur * 2])
			{
				visited[cur * 2] = visited[cur] + 1;
				q.push(cur * 2);
			}
		}
	}
}

int main()
{
	scanf("%d %d", &n, &k);
	printf("%d", bfs());
	return 0;
}