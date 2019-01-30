#include <stdio.h>
#include <string.h>

int n, answer, maxNum;
int num[100000];
bool chk[100000];

void binary(int low, int high)
{
	if (low > high || high > maxNum || low < 1) return;

	int mid = (low + high) / 2;

	// i��° �ε������� i+mid���� �����ϴ��� üũ
	int cnt; // �����ϴ� ���� ī����
	memset(chk, 0, (maxNum + 1));

	for (int i = 0; i < n - mid + 1; i++)
	{
		cnt = 0;
		for (int j = 0; j < mid; j++)
		{
			if (chk[num[i + j]])
			{
				for (int k = 0; k <= j; k++)
					if (chk[num[i + k]]) chk[num[i + k]] = 0;
				break;
			}

			chk[num[i + j]] = 1;
			cnt++;
		}
		if (cnt == mid)
		{
			answer = mid;
			return binary(mid + 1, high);
		}
	}

	if (cnt != mid) return binary(low, mid - 1);
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &num[i]);
		if (maxNum < num[i]) maxNum = num[i];
	}

	binary(1, maxNum);
	printf("%d", answer);

	return 0;
}