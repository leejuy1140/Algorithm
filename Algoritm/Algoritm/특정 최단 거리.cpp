#include <stdio.h>
#include <vector>
using namespace std;

const int MAX = 1001;

int n, m, a, b;
int myGraph[MAX][MAX];


int main()
{
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++)
	{
		int aa, bb, cc;
		scanf("%d %d %d", &aa, &bb, &cc);
		myGraph[aa][bb] = cc;
		myGraph[bb][aa] = cc;
	}
	scanf("%d %d", &a, &b);


	return 0;
}