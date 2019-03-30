#include <stdio.h>
#include <algorithm>
using namespace std;

const int MAX = 100010;

int main()
{
	int n, num[MAX], dp[MAX];
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &num[i]);

/*
	�������� ������
	ī�� ���̴� ������ �ִ� ������ ���ѵ�.
	����, ���� �ڿ����̹Ƿ� �߰��� �۾����ٰ� �ٽ� Ŀ�� ���ɼ��� ����.
	(��ư ������� ī�� ���̿� ����)

	��, ������ ������ ���ѵǾ� ���� �ʰ�, ������ �ֱ� ������ ������.
*/

	dp[0] = num[0];
	int answer = dp[0];
	for (int i = 1; i < n; i++)
	{
		dp[i] = max(num[i], dp[i - 1] + num[i]);
		answer = max(answer, dp[i]);
	}
	printf("%d", answer);

	return 0;
}