/*
1: 0
2 ~ 7: 2 --- 1
8 ~ 19: 3 --- 3
20 ~ 37: 4 --- 6
38 ~ 61: 5 ---- 10
*/

#include <iostream>
using namespace std;

int main()
{
	int n;
	cin >> n;
	if (n == 1)
	{
		cout << 1;
		return 0;
	}

	int answer = 2;
	int a = 2, b = 7, add = 6;
	while (n < a || n > b)
	{
		a += add;
		add += 6;
		b += add;
		answer++;
	}
	cout << answer;
	return 0;
}