#include <stdio.h>
#include <climits>
#include <vector>
#include <queue>
using namespace std;

vector<int> dijkstra(vector<vector<pair<int, int>>> &town, int s)
{
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	vector<int> dist(town.size(), INT_MAX);
	pq.push(pair<int, int>(0, s));
	dist[s] = 0;

	while (!pq.empty())
	{
		pair<int, int> cur = pq.top();
		pq.pop();

		for (int i = 0; i < town[cur.second].size(); i++)
		{
			int nextHome = town[cur.second][i].first;
			int nextDist = cur.first + town[cur.second][i].second;
			if (nextDist < dist[nextHome])
			{
				dist[nextHome] = nextDist;
				pq.push(pair<int, int>(nextDist, nextHome));
			}
		}
	}
	return dist;
}

int main()
{
	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);
	vector<vector<pair<int, int>>> forward(n + 1), reverse(n + 1);
	for (int i = 0; i < m; i++)
	{
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		forward[a].push_back(pair<int, int>(b, c));
		reverse[b].push_back(pair<int, int>(a, c));
	}

	/*
		�ܹ��� �׷����̱� ������,
		��Ƽ���� ������ ������ ���ư��� ���� ���ͽ�Ʈ�� �� ���̸� ������,
		������ ������ ��Ƽ�� ���� ���� ������ �� ��ŭ ���ͽ�Ʈ�� �������Ѵ�.

		���� ȿ������ ������� ������ �׷����� �̿��ϸ�,
		������ ������ ��Ƽ�� ���� ���� ���ͽ�Ʈ�� �� ������ ���� �� �ִ� !!!
	*/

	vector<int> toParty = dijkstra(reverse, k);
	vector<int> toHome = dijkstra(forward, k);
	
	int answer = 0;
	for (int i = 1; i <= n; i++)
	{
		if(toParty[i] + toHome[i] > answer)
			answer = toParty[i] + toHome[i];
	}
	printf("%d\n", answer);

	return 0;
}