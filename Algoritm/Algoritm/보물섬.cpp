#include <stdio.h>
#include <queue>
using namespace std;

const int MAX = 51;

bool visited[MAX][MAX];
int n, m, map[MAX][MAX]; // За, ї­
int dir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };


int main()
{
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++)
	{
		getchar();
		for (int j = 0; j < n; j++)
			scanf("%1c", &map[i][j]);
	}


	return 0;
}