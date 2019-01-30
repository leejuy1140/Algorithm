#include <stdio.h>
#include <vector>
using namespace std;

int n, cnt;
void showPath(vector<int> path)
{
	for (int i = 0; i < path.size(); i++)
	{
		if (i) printf("+");
		printf("%d", path[i]);
	}
	printf("\n");
}

void division(vector<int> &path, int cur, int sum)
{
	if (!cur || sum > n) return;
	if (sum == n)
	{
		cnt++;
		showPath(path);
		return;
	}

	for (int i = cur; i > 0; i--)
	{
		path.push_back(i);
		division(path, i, sum + i);
		path.pop_back();
	}
}

int main()
{
	scanf("%d", &n);

	vector<int> path;
	division(path, n-1, 0);
	printf("%d\n", cnt);

	return 0;
}