#include <stdio.h>

const int MAX = 100005;

int n, S;
int arr[MAX];

/* ������ ���� interval��ŭ ������ ��,
   �� ���� S�̻��� ��찡 �ִ°�?      */
bool check(int interval) // O(N)
{
	int sum = 0;
	for (int i = 0; i < interval; i++) sum += arr[i];
	if (sum >= S) return true;

	for (int i = 0; i < n - interval; i++) {
		sum = sum - arr[i] + arr[i + interval];
		if (sum >= S) return true;
	}
	return false;
}

int main()
{
	scanf("%d %d", &n, &S);
	for (int i = 0; i < n; i++)
		scanf("%d", &arr[i]);

	if (check(1)) { // ���� O�� ���
		printf("1\n");
		return 0;
	}
	if (!check(n)) { // ���� X�� ���
		printf("-1\n");
		return 0;
	}

	int s = 1, e = n;
	while (s < e) {
		int mid = (s + e) / 2;
		if (check(mid)) e = mid - 1;
		else            s = mid + 1;
	}
	printf("%d\n", s);

	return 0;
}