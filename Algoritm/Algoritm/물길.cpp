#include <stdio.h>
#include <string.h>
#include <vector>
#include <queue>
using namespace std;

const int MAX = 100005;
const int QUOTIENT = 1000000007;

int n;
vector<char> visited;
vector<vector<int>> table;
vector<vector<pair<int, int>>> graph;

void bfs(int s)
{
	queue<pair<int, int>> q;
	q.push(make_pair(s, 1));
	visited[s] = 1;
	
	while (!q.empty())
	{
		pair<int, int> cur = q.front();
		q.pop();

		for (int i = 0; i < graph[cur.first].size(); i++)
		{
			int next = graph[cur.first][i].first;
			long long cost = (long long)cur.second * graph[cur.first][i].second;
			cost %= QUOTIENT;

			if (s != next && !table[s][next])
			{
				table[s][next] = cost;
				table[next][s] = cost;
			}

			if (!visited[next])
			{
				q.push(make_pair(next, cost));
				visited[next] = 1;
			}
		}
	}
}

int main()
{
	scanf("%d", &n);
	visited.resize(n + 1);
	graph.resize(n + 1);
	table.resize(n + 1);
	for (int i = 0; i <= n; i++)
		table[i].resize(n + 1);

	for (int i = 0; i < n-1; i++)
	{
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		graph[a].push_back(make_pair(b, c));
		graph[b].push_back(make_pair(a, c));
	}

	for (int i = 1; i < n; i++)
	{
		for (int j = i + 1; j <= n; j++)
		{
			if (!table[i][j])
			{
				memset(&visited[0], 0, n + 1);
				bfs(i);
			}
		}
	}

	long long answer = 0;
	for (int i = 1; i < n; i++)
		for (int j = i + 1; j <= n; j++)
			answer += table[i][j];
	printf("%lld\n", answer % QUOTIENT);

	return 0;
}