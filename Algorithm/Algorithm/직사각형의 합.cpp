#include <stdio.h>
#include <vector>
using namespace std;

const int MAX = 1000;

int main()
{
	int n, m, q;
	scanf("%d %d %d", &n, &m, &q);

	vector <vector<int>> square(n, vector<int>(m));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			scanf("%d", &square[i][j]);

	vector <vector<int>> sum = square;
	for (int i = 0; i < n; i++)
	{
		for (int j = 1; j < m; j++)
			sum[i][j] += sum[i][j - 1];
	}
	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			sum[i][j] += sum[i - 1][j];
	}
	while (q--)
	{
		int a, b, c, d;
		scanf("%d %d %d %d", &a, &b, &c, &d);

		int tmp;
		if	   (!a && !b) tmp = 0;
		else if(!a)		  tmp = sum[c][b - 1];
		else if(!b)		  tmp = sum[a - 1][d];
		else			  tmp = sum[a - 1][d] + sum[c][b - 1] - sum[a - 1][b - 1];
		printf("%d\n", sum[c][d] - tmp);
	}

	return 0;
}