#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	int x, y, w, h;
	cin >> x >> y >> w >> h;

	int answer = 99999999;
	if (abs(x - w) < answer) answer = abs(x - w);
	if (x < answer)			 answer = x;
	if (abs(y - h) < answer) answer = abs(y - h);
	if (y < answer)			 answer = y;
	cout << answer;

	return 0;
}