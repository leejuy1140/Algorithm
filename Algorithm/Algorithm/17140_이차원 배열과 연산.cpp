#include <iostream>
#include <algorithm>
using namespace std;

const int MAX = 101;

int rsz, csz; // ���� ��� �� ũ��.
int r, c, k, A[MAX][MAX], cnt[MAX];
struct Set { int num, cnt; } newA[MAX];

bool compare(Set& a, Set& b)
{
	if (a.cnt > b.cnt) return false;
	else if (a.cnt == b.cnt)
	{
		if (a.num > b.num) return false;
		else			   return true;
	}
	else return true;
}

int Do_R_Operation()
{
	int max_csz = 0; // ���� �� �ִ� ���� ũ��.
	for (int i = 1; i <= rsz; i++)
	{
		// 1. ���� �� ���� ī����.
		for (int j = 1; j <= csz; j++)
			if (A[i][j]) cnt[A[i][j]]++;

		// 2. ���ڿ� ������ ���� ����.
		int new_idx = 0;
		for (int k = 1; k < MAX; k++)
		{
			if (cnt[k])
			{
				new_idx++;
				newA[new_idx].num = k;	    // ����
				newA[new_idx].cnt = cnt[k]; // ����
				cnt[k] = 0; // �ʱ�ȭ
			}
		}

		// 3. ���� �������� ����. (������ ���� ��������)
		sort(&newA[1], &newA[new_idx + 1], compare);

		// 4. ���� ���� ���� �ִ� ũ�� ����.
		max_csz = max_csz > (new_idx * 2) ? max_csz : (new_idx * 2);

		// 5. A �迭�� ���� ���� �� ����.
		int j = 1;
		for (int k = 1; k <= new_idx; k++)
		{
			A[i][j++] = newA[k].num;
			A[i][j++] = newA[k].cnt;
		}
		A[i][j] = -1; // �� ǥ��.
	}

	// 6. ���� �� ���� �ִ� ũ��� 0 �е�.
	for (int i = 1; i <= rsz; i++)
	{
		for (int j = max_csz + 1; j >= 0; j--)
		{
			if (A[i][j] == -1)
			{
				A[i][j] = 0;
				break;
			}
			A[i][j] = 0;
		}
	}
	return max_csz;
}

int Do_C_Operation()
{
	int max_rsz = 0;
	for (int i = 1; i <= csz; i++)
	{
		for (int j = 1; j <= rsz; j++)
			if (A[j][i]) cnt[A[j][i]]++;

		int new_idx = 0;
		for (int k = 1; k < MAX; k++)
		{
			if (cnt[k])
			{
				new_idx++;
				newA[new_idx].num = k;	    // ����
				newA[new_idx].cnt = cnt[k]; // ����
				cnt[k] = 0; // �ʱ�ȭ
			}
		}
		sort(&newA[1], &newA[new_idx + 1], compare);
		max_rsz = max_rsz > (new_idx * 2) ? max_rsz : (new_idx * 2);

		int j = 1;
		for (int k = 1; k <= new_idx; k++)
		{
			A[j++][i] = newA[k].num;
			A[j++][i] = newA[k].cnt;
		}
		A[j][i] = -1;
	}

	for (int i = 1; i <= csz; i++)
	{
		for (int j = max_rsz + 1; j >= 0; j--)
		{
			if (A[j][i] == -1)
			{
				A[j][i] = 0;
				break;
			}
			A[j][i] = 0;
		}
	}
	return max_rsz;
}

int main()
{
	rsz = csz = 3;
	cin >> r >> c >> k;
	for (int i = 1; i <= rsz; i++)
		for (int j = 1; j <= csz; j++)
			cin >> A[i][j];

	int answer = 0;
	while (A[r][c] != k)
	{
		if (rsz >= csz) csz = Do_R_Operation();
		else			rsz = Do_C_Operation();

		answer++;
		if (answer > 100)
		{
			answer = -1;
			break;
		}
	}
	cout << answer;
}