#include <stdio.h>
#include <algorithm>
using namespace std;
int main()
{
	/*
		������ b���,
		b�� fx ���� a���� �۰�, (b+1)�� fx ���� a���� ŭ.
	*/

	uint64_t a;
	scanf("%llu", &a);

	uint64_t pre = 0; // f(x) ����� a���� ������ 1�� ����
	uint64_t max = sqrt(a) + 1;
	uint64_t mid = max / 2;
	while (1)
	{
		if (max < mid) break;

		uint64_t res = mid * mid + mid;

		// a�� ������ �ش� ���� ����
		if (res == a)
		{
			printf("%d", mid);
			break;
		}

		// a���� ������ Ŀ���� ���� ���� ������ ���ο� �߰� �� ���
		if (res < a)
		{
			pre = mid;
			mid += (max - mid) / 2;

			// ���ο� �߰� ���� ���� ���� �����ϴٸ�, ���� ���� ����
			if (pre == mid)
			{
				printf("%d", pre);
				break;
			}
		}
		else
		{
			// a���� ���� �� ����� ���� ������ ��� ���ݾ� �ٿ�����
			if (!pre)
			{
				max = mid;
				mid /= 2;
			}

			// ������ a���� �۾Ҵµ�, �̹��� a���� ũ�� ���� ���� ����
			else
			{
				printf("%d", pre);
				break;
			}
		}
	}

	return 0;
}