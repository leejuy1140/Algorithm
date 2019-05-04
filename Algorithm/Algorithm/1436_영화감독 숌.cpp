#include <iostream>
using namespace std;

bool Check666(int _num)
{
	int cnt = 0;	   // 6 개수 카운팅.
	bool flag = false; // 연속 6을 찾기 위한 플래그.
	
	while (_num)
	{
		int remain = _num % 10;
		if (remain == 6)
		{
			if (flag == false) // 처음 나온 6이라면 연속 플래그 설정.
			{
				flag = true;
				cnt++;
			}
			else cnt++;		   // 연속으로 나온 6이라면 계속 카운팅.
		}
		else // 6이 아니라면 연속 플래그와 카운팅 초기화. 
		{
			flag = false;
			cnt = 0;
		}

		if (cnt >= 3) return true;
		_num /= 10;
	}
	return false;
}

int main()
{
	int n;
	cin >> n;

	int seq = 1;
	int num = 666;
	while (seq != n)
	{
		num++;
		if(Check666(num)) seq++;
	}
	cout << num;

	return 0;
}