#include <iostream>
using namespace std;

const int MAX = 27;

int n, r;
bool check[MAX];
char answer[MAX];

void solution(int idx)
{
	if (idx == r)
	{
		for (int i = 0; i < idx; i++)
			cout << answer[i];
		cout << endl;
		return;
	}

	for (int i = 0; i < n; i++)
	{
		if (check[i]) continue;

		check[i] = true;
		answer[idx] = i + 'a';
		solution(idx + 1);
		check[i] = false;
	}
}

int main()
{
	cin >> n >> r;
	solution(0);
	return 0;
}