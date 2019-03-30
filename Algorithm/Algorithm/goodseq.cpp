#include <stdio.h>

int n, sequence[80];

bool chkGoodSeq(int idx)
{
	int same = 1, cnt = 0;
	int r = idx;
	int l = idx - same;
	
	while (1)
	{
		// ���� �ε����� ������ �Ѿ���Ƿ�, ���� ����
		if (same > (idx + 1) / 2) return true;

		// idx���� same ������ŭ�� ������ ���� ������ �����ϹǷ�, ���� ����
		if (same == cnt) return false;

		if (sequence[l] == sequence[r])
		{
			cnt++;
			r--;
			l--;
		}
		else
		{
			cnt = 0;
			same++;
			r = idx;
			l = idx - same;
		}
	}
}

int flag = 0;
void goodMinSeq(int idx, int num)
{
	// n�ڸ����� ������ ��������� ����
	if (flag) return;
	if (idx == n) { flag = 1; return; }

	sequence[idx] = num;

	// ���� �����̸� ���� �ε��� ä��������
	if (chkGoodSeq(idx))
	{
		for (int i = 1; i <= 3; i++)
			goodMinSeq(idx + 1, i);
	}
}

int main()
{
	scanf("%d", &n);

	goodMinSeq(0, 1);
	for (int i = 0; i < n; i++)
		printf("%d", sequence[i]);

	return 0;
}