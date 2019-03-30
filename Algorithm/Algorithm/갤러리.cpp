#include <stdio.h>
#include <vector>
using namespace std;

#define VISIT 1
#define CCTV 2

int d, p, answer;
vector<char> visited;
vector<vector<int>> tree;

int dfs(int node) // CCTV 설치 여부 반환
{
	visited[node] = VISIT; // dfs 중 다시 돌아오지 않기 위해, 방문 표시.

	int flag = 0; // 자식 중 CCTV 없는 애가 있으면, 플래그 올림.
	for (int i = 0; i < tree[node].size(); i++)
	{
		int childNode = tree[node][i];
		if (visited[childNode]) continue;

		/* 만약 cctv에 포함되지 않는 자식이 하나라도 있다면,
		   현재 노드에 카메라 설치 !						 */
		if (dfs(childNode) != CCTV) flag = 1;
	}

	if (flag) // 자식 중에 CCTV 없는 자식이 있으니,
	{
		answer++; // CCTV 설치
		visited[node] = CCTV; // CCTV 사용 표시

		for (int i = 0; i < tree[node].size(); i++) // 모든 자식들 CCTV 사용.
		{
			int childNode = tree[node][i];
			if (visited[childNode] != CCTV) visited[childNode] = CCTV;
		}
	}
	return visited[node]; // 현재 노드의 상태 반환
}

int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		answer = 0;
		scanf("%d %d", &d, &p);
		tree.resize(d);
		visited.resize(d);
		for (int i = 0; i < p; i++)
		{
			int a, b;
			scanf("%d %d", &a, &b);
			tree[a].push_back(b);
			tree[b].push_back(a);
		}

		for (int i = 0; i < d; i++)
		{
			if (!tree[i].size()) { answer++; continue; } // 연결된 노드가 없으면, 따로 설치.
			
			if (visited[i] != CCTV) // 연결된 노드가 있고 설치 안됐으면, 설치하러 출발.
				if(dfs(i) != CCTV) answer++; // 자식들은 다 설치됐는데 나만 안된 경우, 설치.
		}
		printf("%d\n", answer);

		tree.clear();
		visited.clear();
	}
	return 0;
}