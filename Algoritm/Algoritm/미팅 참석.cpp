#include <stdio.h>
#include <vector>
using namespace std;

const int MAX = 100005;

int main()
{
	int n;
	pair<int, int> data[MAX];
	
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d %d", &data[i].first, &data[i].second);


	return 0;
}