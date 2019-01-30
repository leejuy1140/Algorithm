#include <stdio.h>

int n, sequence[80];

bool chkGoodSeq(int idx)
{
	int same = 1, cnt = 0;
	int r = idx;
	int l = idx - same;
	
	while (1)
	{
		// 비교할 인덱스가 절반을 넘어갔으므로, 좋은 수열
		if (same > (idx + 1) / 2) return true;

		// idx부터 same 개수만큼의 수열은 인접 수열과 동일하므로, 나쁜 수열
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
	// n자리까지 수열을 만들었으면 종료
	if (flag) return;
	if (idx == n) { flag = 1; return; }

	sequence[idx] = num;

	// 좋은 수열이면 다음 인덱스 채워나가기
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