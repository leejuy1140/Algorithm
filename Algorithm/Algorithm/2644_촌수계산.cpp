#include <iostream>
#include <vector>
using namespace std;

const int MAX = 101;

bool visited[MAX];
vector<vector<int>> family(MAX);

int dfs(int cur, int dest, int cnt)
{
	if (cur == dest) return cnt; // 원하는 친척을 만났으면, 촌수 반환.

	visited[cur] = true; // 현재 친척 방문 체크.
	for (int i = 0; i < family[cur].size(); i++) // 다음 친적 만나러 감.
	{
		if (visited[family[cur][i]]) continue; // 방문했던 친적은 패스.

		// 방문하고 온 결과 원하는 친적을 만났으면, 계속하여 촌수 반환.
		int ret = dfs(family[cur][i], dest, cnt + 1);
		if (ret != -1) return ret;
	}
	return -1; // 원하는 친적을 못만났기 때문에 -1 반환.
}

int main()
{
	int n, m, a, b;
	cin >> n >> a >> b >> m;
	for (int i = 0; i < m; i++)
	{
		int x, y;
		cin >> x >> y;
		family[x].push_back(y);
		family[y].push_back(x);
	}
	cout << dfs(a, b, 0);
	return 0;
}