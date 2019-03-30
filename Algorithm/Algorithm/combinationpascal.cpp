#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

int main() {

	//Please Enter Your Code Here
	int n, m;
	scanf("%d %d", &n, &m);

	vector<int> up;
	for (int i = n; i > max(m, n - m); i--)
		up.push_back(i);

	vector<int> down;
	for (int i = min(m, n - m); i > 0; i--)
		down.push_back(i);

	for (int i = 0; i < up.size(); i++)
	{
		for (int j = 0; j < down.size(); j++)
		{
			if (up[i] % down[j] == 0)
			{
				up[i] /= down[j];
				down[j] = 1;
			}
		}
	}

	uint64_t upper = 1;
	for (int i = 0; i < up.size(); i++)
		upper *= up[i];

	uint64_t lower = 1;
	for (int j = 0; j < down.size(); j++)
		lower *= down[j];

	printf("%llu\n", upper / lower);

	return 0;
}