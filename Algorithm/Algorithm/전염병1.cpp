#include <stdio.h>
#include <queue>
using namespace std;

int n, k, cnt;
bool chk[100001]; // 인덱스 1부터 사용

void bfs(int start)
{
	queue<int> q;
	q.push(start);
	chk[start] = 1;
	cnt++;

	while (!q.empty())
	{
		int curTown = q.front();
		q.pop();

		for (int i = 0; i < 2; i++)
		{
			int nextTown;
			if (i == 0) nextTown = 2 * curTown;
			else        nextTown = curTown / 3;

			if (chk[nextTown]) continue;
			if (nextTown > n || nextTown < 1) continue;

			q.push(nextTown);
			chk[nextTown] = 1;
			cnt++;
		}
	}
}

int main()
{
	// i->2i & i->i/3
	scanf("%d %d", &n, &k);
	bfs(k);
	printf("%d\n", cnt);
	return 0;
}