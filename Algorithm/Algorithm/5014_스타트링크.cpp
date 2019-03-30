#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

int F, S, G, U, D;
struct Floor { int level; int num; };
vector<int> visited;

int solution(Floor _s)
{
	queue<Floor> q;
	q.push(_s);
	visited[_s.level] = 1;

	int min_num = 2147483647;
	while (!q.empty())
	{
		Floor cur = q.front();
		q.pop();

		if (cur.level == G)	// 해당 층에 도달하면 횟수 반환
		{
			min_num = min(cur.num, min_num);
		}
		else
		{
			if (cur.level + U <= F) // 올라갈 수 있으면, 올라감
			{
				if (!visited[cur.level + U])
				{
					q.push({ cur.level + U, cur.num + 1 });
					visited[cur.level + U] = 1;
				}
			}
			if (cur.level - D > 0) // 내려갈 수 있으면, 내려감
			{
				if (!visited[cur.level - D])
				{
					q.push({ cur.level - D, cur.num + 1 });
					visited[cur.level - D] = 1;
				}
			}
		}
	}

	return min_num;
}

int main()
{
	scanf("%d %d %d %d %d", &F, &S, &G, &U, &D);

	visited.resize(F + 1);
	for (int i = 0; i <= F; i++) visited[i] = 0;

	Floor s = { S, 0 };
	int result = solution(s);
	if (result != 2147483647) printf("%d\n", result);
	else					  printf("use the stairs\n");

	return 0;
}