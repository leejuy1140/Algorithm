#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;

int gear[5][8], spin[5]; // �� ��Ϲ����� ȸ�� ���� ����.

/* _cur �� _dir �������� ������ ��, ȸ���ϴ� ��� üũ. */
void CheckGear(int _cur, int _dir)
{
	spin[_cur] = _dir;					// 1. ���� ��� ȸ��.
	for (int i = _cur + 1; i <= 4; i++) // 2. ������ ��� üũ.
	{
		if (gear[i - 1][2] == gear[i][6]) spin[i] = 0;
		else							  spin[i] = spin[i - 1] * -1;
	}
	for (int i = _cur - 1; i >= 1; i--) // 3. ���� ��� üũ.
	{
		if (gear[i + 1][6] == gear[i][2]) spin[i] = 0;
		else							  spin[i] = spin[i + 1] * -1;
	}
}

/* _cur �� _dir �������� ȸ��. */
void SpinGear(int _cur, int _dir)
{
	if (_dir == -1) // �ݽð�
	{
		int start = gear[_cur][0];
		for (int i = 0; i < 7; i++)
			gear[_cur][i] = gear[_cur][i + 1];
		gear[_cur][7] = start;
	}
	if (_dir == 1)	// �ð�
	{
		int end = gear[_cur][7];
		for (int i = 7; i > 0; i--)
			gear[_cur][i] = gear[_cur][i - 1];
		gear[_cur][0] = end;
	}
}

int main()
{
	for (int i = 1; i <= 4; i++)
		for (int j = 0; j < 8; j++)
			scanf("%1d", &gear[i][j]);
	
	int k;
	scanf("%d", &k);
	while (k--)
	{
		int num, dir;
		scanf("%d %d", &num, &dir);

		CheckGear(num, dir);
		for (int i = 1; i <= 4; i++) SpinGear(i, spin[i]);
	}

	int answer = 0;
	if (gear[1][0]) answer += 1;
	if (gear[2][0]) answer += 2;
	if (gear[3][0]) answer += 4;
	if (gear[4][0]) answer += 8;
	printf("%d", answer);

	return 0;
}