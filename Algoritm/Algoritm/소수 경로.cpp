#include <stdio.h>
#include <string.h>
#include <queue>
using namespace std;

const int MAX = 10000;
const int BOTTOM = 1000;

int a, b;
bool visited[MAX], table[MAX]; // 1: 소수 X

bool canChange(queue<pair<int, int>> &_q, int num, int level)
{
	if (num >= MAX || num < BOTTOM) return false;
	if (table[num] || visited[num]) return false;

	_q.push(pair<int, int>(num, level + 1));
	visited[num] = 1;
	return true;
}

int bfs()
{
	queue<pair<int, int>> q; // 소수, 단계
	q.push(pair<int, int>(a, 0));
	visited[a] = 1;

	int tmp1, tmp2, nextNum;
	while (!q.empty())
	{
		pair<int, int> cur = q.front(); q.pop();
		if (cur.first == b) return cur.second;

		// 1. 1000의 자리 바꾸기
		tmp1 = cur.first % 1000;
		for (int i = 1; i <= 9; i++)
		{
			nextNum = tmp1 + (i * 1000);
			canChange(q, nextNum, cur.second);
		}

		// 2. 100의 자리 바꾸기
		tmp1 = (cur.first / 1000) * 1000;
		tmp2 = (cur.first % 100);
		for (int i = 0; i <= 9; i++)
		{
			nextNum = tmp1 + (i * 100) + tmp2;
			canChange(q, nextNum, cur.second);
		}

		// 3. 10의 자리 바꾸기
		tmp1 = (cur.first % 1000);
		tmp2 = ((cur.first / 1000) * 1000 + (tmp1 / 100) * 100) + (tmp1 % 10);
		for (int i = 0; i <= 9; i++)
		{
			nextNum = tmp2 + (i * 10);
			canChange(q, nextNum, cur.second);
		}

		// 4. 1의 자리 바꾸기
		tmp1 = cur.first - (cur.first % 10);
		for (int i = 0; i <= 9; i++)
		{
			nextNum = tmp1 + i;
			canChange(q, nextNum, cur.second);
		}
	}
	return -1;
}

int main()
{
	int t;
	scanf("%d", &t);

	for (int prime = 2; prime < MAX; prime++)
	{
		if (table[prime]) continue;
		for (int i = 0; i < MAX; i++)
		{
			if (table[i] || i <= prime) continue;
			if (i % prime == 0) table[i] = 1;
		}
	}

	while (t--)
	{
		scanf("%d %d", &a, &b);

		int ret = bfs();
		if (ret == -1) printf("impossible\n");
		else	  	   printf("%d\n", ret);

		memset(visited, 0, MAX);
	}
	return 0;
}