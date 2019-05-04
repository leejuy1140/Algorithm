#include <iostream>
using namespace std;

bool Check666(int _num)
{
	int cnt = 0;	   // 6 ���� ī����.
	bool flag = false; // ���� 6�� ã�� ���� �÷���.
	
	while (_num)
	{
		int remain = _num % 10;
		if (remain == 6)
		{
			if (flag == false) // ó�� ���� 6�̶�� ���� �÷��� ����.
			{
				flag = true;
				cnt++;
			}
			else cnt++;		   // �������� ���� 6�̶�� ��� ī����.
		}
		else // 6�� �ƴ϶�� ���� �÷��׿� ī���� �ʱ�ȭ. 
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