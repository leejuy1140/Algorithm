/*
21:46 ����.
00:00 ����.
00�ð� 00�� �ҿ�.

1) ���� ����
- R ����: �� ���� ����. (�� ���� >= �� ����)
- C ����: �� ���� ����. (�� ���� < �� ����)
- ���� ���
  ������ ������ ���� Ƚ�� ��������.
  ���� Ƚ���� ������ ���� ��������.
  ���� �� �迭�� ���ڿ� ���� Ƚ�� ������ ����.
- ���� ��
  R ���� �� ���� ũ�Ⱑ ���� ū ���� �������� ��� ���� ũ�� ����.
  C ���� �� ���� ũ�Ⱑ ���� ū ���� �������� ��� ���� ũ�� ����.
  �� ���� 0���� �е�. (���� �� 0�� ����.)
- �� �Ǵ� ���� ũ�Ⱑ 100�� �Ѿ��, ó�� 100���� ���.
- A[r][c] == k�� �����ϴ� �ּ� ���� �ð� ���. (100 �ʰ� �� -1 ���.)
2) ����
const int MAX = 101;
const int INF = 999999;
int rSize, cSize; // ��� ���� ũ��.
struct MyA { int num, cnt; } myA[MAX]; 
3) ����
1. ��� ���� ũ�� �� �� ������ ���� �Լ� ȣ��.
 2. �ϳ��� �� �Ǵ� ���� ���� �� ������ myA �迭�� ī����.
 3. myA �迭 �������� ����.
 4. ���� �� ���� ���ǿ� ���� A �迭�� ����.
 5. A�� �ִ� ũ�� Ȯ�� �� ����.
 6. ��� �� �Ǵ� ���� ���� ������ ������ �� �ִ� ũ�⿡ ���� 0 �е�.
7. A[r][c]�� k�� ���� ���.
4) ����� ��
5) �ʱ�ȭ �ʿ��� ����
myA[i].num = i;   // ���� �Ŀ��� ���ڸ� ã�� �� �ֵ���.
myA[i].cnt = INF;
6) ����ġ��
*/

#include <iostream>
#include <algorithm>
using namespace std;

const int MAX = 105;
const int INF = 999999;

int rSize, cSize; // ��� ���� ũ��.
int r, c, k, A[MAX][MAX];
struct MyA { int num, cnt; } myA[MAX];

bool compare(MyA& a, MyA& b)
{
	if (a.cnt > b.cnt) return false;
	else if (a.cnt == b.cnt)
	{
		if (a.num > b.num) return false;
		else			   return true;
	}
	else return true;
}

void Do_R_Operation()
{
	int newSize = 0;
	for (int i = 0; i < rSize; i++)
	{
		// 2. �ϳ��� �� �Ǵ� ���� ���� �� ������ myA �迭�� ī����.
		for (int j = 0; j < cSize; j++)
		{
			if (A[i][j] == 0) continue;

			if (myA[A[i][j]].cnt == INF)
			{
				myA[A[i][j]].num = A[i][j];
				myA[A[i][j]].cnt = 1;
			}
			else myA[A[i][j]].cnt++;
		}

		// 3. myA �迭 �������� ����.
		sort(&myA[0], &myA[MAX], compare);

		// 4. ���� �� ���� ���ǿ� ���� A �迭�� ����.
		int A_idx = 0;
		for (int j = 0; j < MAX; j++)
		{
			if (A_idx > 100 || myA[j].cnt == INF) break;

			A[i][A_idx++] = myA[j].num;
			A[i][A_idx++] = myA[j].cnt;
			myA[j].cnt = INF;
		}
		A[i][A_idx] = -1;

		// 5. A�� �ִ� ũ�� Ȯ�� �� ����.
		if (newSize < A_idx) newSize = A_idx;
	}

	// 6. �ִ� ũ�⿡ ���� 0 �е�.
	for (int i = 0; i < rSize; i++)
	{
		for (int j = newSize; j >= 0; j--)
		{
			if (A[i][j] == -1)
			{
				A[i][j] = 0;
				break;
			}
			A[i][j] = 0;
		}
	}
	
	rSize = newSize;
	return;
}

void Do_C_Operation()
{
	int newSize = 0;
	for (int i = 0; i < cSize; i++)
	{
		// 2. �ϳ��� �� �Ǵ� ���� ���� �� ������ myA �迭�� ī����.
		for (int j = 0; j < rSize; j++)
		{
			if (A[j][i] == 0) continue;

			if (myA[A[j][i]].cnt == INF)
			{
				myA[A[j][i]].num = A[j][i];
				myA[A[j][i]].cnt = 1;
			}
			else myA[A[j][i]].cnt++;
		}

		// 3. myA �迭 �������� ����.
		sort(&myA[0], &myA[MAX], compare);

		// 4. ���� �� ���� ���ǿ� ���� A �迭�� ����.
		int A_idx = 0;
		for (int j = 0; j < MAX; j++)
		{
			if (A_idx > 100 || myA[j].cnt == INF) break;

			A[A_idx++][i] = myA[j].num;
			A[A_idx++][i] = myA[j].cnt;
			myA[j].cnt = INF;
		}
		A[A_idx][i] = -1;

		// 5. A�� �ִ� ũ�� Ȯ�� �� ����.
		if (newSize < A_idx) newSize = A_idx;
	}

	// 6. �ִ� ũ�⿡ ���� 0 �е�.
	for (int i = 0; i < cSize; i++)
	{
		for (int j = newSize; j >= 0; j--)
		{
			if (A[j][i] == -1)
			{
				A[j][i] = 0;
				break;
			}
			A[j][i] = 0;
		}
	}

	cSize = newSize;
	return;
}

int main()
{
	rSize = cSize = 3;
	for (int i = 0; i < MAX; i++)
	{
		myA[i].num = i;
		myA[i].cnt = INF;
	}

	scanf("%d %d %d", &r, &c, &k);
	for (int i = 0; i < rSize; i++)
		for (int j = 0; j < cSize; j++)
			scanf("%d", &A[i][j]);

	int time = 0;
	while(A[r - 1][c - 1] != k)
	{ 
		// 1. ��� ���� ũ�� �� �� ������ ���� �Լ� ȣ��.
		if (rSize >= cSize) Do_R_Operation();
		else				Do_C_Operation();

		/*printf("\n");
		for (int i = 0; i < rSize; i++)
		{
			for (int j = 0; j < cSize; j++)
				printf("%d ", A[i][j]);
			printf("\n");
		}*/

		time++;
		if (time > 100)
		{
			time = -1;
			break;
		}
	}
	printf("%d\n", time);

	return 0;
}