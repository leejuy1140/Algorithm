#include <iostream>
#include <vector>
using namespace std;

const int MAX = 15;
const int INF = 1999999999;

vector<int> op;
bool check[MAX];
int n, num[MAX], maxNum = -INF, minNum = INF;

/* idx번째 연산자를 이용해 현재 값과 계산 후, 결과 반환. */
int Calculate(int idx, int val, int cnt)
{
	int newVal = val;
	if (op[idx] == 1) return newVal += num[cnt + 1];
	if (op[idx] == 2) return newVal -= num[cnt + 1];
	if (op[idx] == 3) return newVal *= num[cnt + 1];
	if (op[idx] == 4) return newVal /= num[cnt + 1];
}

/* 연산자를 끼워넣는 모든 경우 확인. */
void InsertOperator(int idx, int val, int cnt)
{	
	if (cnt == n - 1) // 다 끼워넣었으면, 값 갱신.
	{
		maxNum = maxNum > val ? maxNum : val;
		minNum = minNum < val ? minNum : val;
		return;
	}

	check[idx] = true;
	for (int i = 0; i < op.size(); i++) // 다음 위치 연산자 찾기.
	{
		if (check[i]) continue;

		int newVal = Calculate(i, val, cnt);
		InsertOperator(i, newVal, cnt + 1);
		check[i] = false;
	}
}


int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &num[i]);
	for (int i = 1; i <= 4; i++)
	{
		int cnt;
		scanf("%d", &cnt);
		while (cnt--) op.push_back(i);
	}

	// i번째 연산자를 시작으로 연산자 끼워넣기.
	for (int i = 0; i < op.size(); i++)
	{
		int val = Calculate(i, num[0], 0);
		InsertOperator(i, val, 1);
		check[i] = false;
	}
	printf("%d\n%d", maxNum, minNum);

	return 0;
}