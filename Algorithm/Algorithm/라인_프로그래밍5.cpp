#include <iostream>
#include <queue>
using namespace std;

const int MAX = 200001;

int cony, brown;
int visited[MAX];
struct Info { int c, b, c_move, time; };

int solution() {
	queue<Info> q;
	q.push({ cony, brown, 0, 0 });
	
	while (!q.empty())
	{
		Info cur = q.front();
		q.pop();
		//printf("%d %d %d\n", cur.c, cur.b, cur.time);

		if (cur.c == cur.b) return cur.time;

		int next_c = cur.c + cur.c_move + 1;
		if (next_c >= MAX) return -1;

		int next_b1 = cur.b + 1;
		if (next_b1 < MAX && next_b1 >= 0)
		{
			if (!cur.time || visited[next_b1] != cur.time)
			{
				q.push({ next_c, next_b1, cur.c_move + 1, cur.time + 1 });
				visited[next_b1] = cur.time;
			}
		}

		int next_b2 = cur.b - 1;
		if (next_b2 < MAX && next_b2 >= 0)
		{
			if (!cur.time || visited[next_b2] != cur.time)
			{
				q.push({ next_c, next_b2, cur.c_move + 1, cur.time + 1 });
				visited[next_b2] = cur.time;
			}
		}

		int next_b3 = cur.b * 2;
		if (next_b3 < MAX && next_b3 >= 0)
		{
			if (!cur.time || visited[next_b3] != cur.time)
			{
				q.push({ next_c, next_b3, cur.c_move + 1, cur.time + 1 });
				visited[next_b3] = cur.time;
			}
		}
	}
	return -1;
}

int main(void) {
	scanf("%d %d", &cony, &brown);
	int answer = solution();
	printf("%d\n", answer);
	return 0;
}