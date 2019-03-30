#include <stdio.h>
#include <queue>
using namespace std;

const int MAX = 100000;

int n;
bool visited[MAX];

bool chkDigits(int num)
{
	int cnt = 0;
	while (num)
	{
		num /= 10;
		cnt++;
	}
	if (cnt > 5) return false;
	else		 return true;
}

int bfs(int num)
{
	queue<pair<int, int>> q;
	q.push(pair<int, int>(num, 0));
	visited[num] = 1;

	while (!q.empty())
	{
		pair<int, int> cur = q.front();
		if (cur.first == n) return cur.second;
		q.pop();

		int newNum = cur.first * 2;
		if (chkDigits(newNum) && !visited[newNum])
		{
			q.push(pair<int, int>(newNum, cur.second + 1));
			visited[newNum] = 1;
		}

		newNum = cur.first / 3;
		if (chkDigits(newNum) && !visited[newNum])
		{
			q.push(pair<int, int>(newNum, cur.second + 1));
			visited[newNum] = 1;
		}
	}
}

int main()
{
	scanf("%d", &n);
	printf("%d", bfs(1));
	return 0;
}