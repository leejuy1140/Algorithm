#include <iostream>
#include <algorithm>
using namespace std;

const int MAX = 101;

int rsz, csz; // 현재 행과 열 크기.
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
	int max_csz = 0; // 정렬 후 최대 열의 크기.
	for (int i = 1; i <= rsz; i++)
	{
		// 1. 숫자 별 개수 카운팅.
		for (int j = 1; j <= csz; j++)
			if (A[i][j]) cnt[A[i][j]]++;

		// 2. 숫자와 개수를 따로 저장.
		int new_idx = 0;
		for (int k = 1; k < MAX; k++)
		{
			if (cnt[k])
			{
				new_idx++;
				newA[new_idx].num = k;	    // 숫자
				newA[new_idx].cnt = cnt[k]; // 개수
				cnt[k] = 0; // 초기화
			}
		}

		// 3. 개수 오름차순 정렬. (같으면 숫자 오름차순)
		sort(&newA[1], &newA[new_idx + 1], compare);

		// 4. 정렬 후의 행의 최대 크기 갱신.
		max_csz = max_csz > (new_idx * 2) ? max_csz : (new_idx * 2);

		// 5. A 배열에 정렬 후의 값 복사.
		int j = 1;
		for (int k = 1; k <= new_idx; k++)
		{
			A[i][j++] = newA[k].num;
			A[i][j++] = newA[k].cnt;
		}
		A[i][j] = -1; // 끝 표시.
	}

	// 6. 정렬 후 열의 최대 크기로 0 패딩.
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
				newA[new_idx].num = k;	    // 숫자
				newA[new_idx].cnt = cnt[k]; // 개수
				cnt[k] = 0; // 초기화
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