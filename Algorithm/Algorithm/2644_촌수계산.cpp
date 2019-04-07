#include <iostream>
#include <vector>
using namespace std;

const int MAX = 101;

bool visited[MAX];
vector<vector<int>> family(MAX);

int dfs(int cur, int dest, int cnt)
{
	if (cur == dest) return cnt; // ���ϴ� ģô�� ��������, �̼� ��ȯ.

	visited[cur] = true; // ���� ģô �湮 üũ.
	for (int i = 0; i < family[cur].size(); i++) // ���� ģ�� ������ ��.
	{
		if (visited[family[cur][i]]) continue; // �湮�ߴ� ģ���� �н�.

		// �湮�ϰ� �� ��� ���ϴ� ģ���� ��������, ����Ͽ� �̼� ��ȯ.
		int ret = dfs(family[cur][i], dest, cnt + 1);
		if (ret != -1) return ret;
	}
	return -1; // ���ϴ� ģ���� �������� ������ -1 ��ȯ.
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