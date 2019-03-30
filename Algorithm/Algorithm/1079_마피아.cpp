#include <stdio.h>
#include <string.h>

const int MAX = 20;
const int DEAD = -999;

int n, mafiaIdx, answer, score[MAX], r[MAX][MAX];

void DayTime(int playerNum, int nightCnt);
void NightTime(int playerNum, int nightCnt);

void DayTime(int playerNum, int nightCnt)
{
	int maxIdx = 0;
	for (int i = 1; i < n; i++)
	{
		if (score[i] == DEAD) continue;
		if (score[i] > score[maxIdx]) maxIdx = i;
	}

	// ���� ���� ����� ���Ǿưų� ���ǾƸ� ������, ����.
	if (maxIdx == mafiaIdx || playerNum - 1 == 1)
	{
		answer = answer > nightCnt ? answer : nightCnt;
		return;
	}

	score[maxIdx] = DEAD;
	return NightTime(playerNum - 1, nightCnt);
}

void NightTime(int playerNum, int nightCnt)
{
	if (playerNum - 1 == 1)
	{
		answer = answer > nightCnt + 1 ? answer : nightCnt + 1;
		return;
	}

	int save[MAX]; // ���� ���� ���� ����.
	memcpy(save, score, sizeof(int) * n);
	
	// ���� ��� ���� Ž������ ����.
	for (int i = 0; i < n; i++)
	{
		// ���Ǿ� �����̰ų� ���� �ù��̸�, �н�.
		if (i == mafiaIdx || score[i] == DEAD) continue;
		
		score[i] = DEAD; // ���̰� ���� ���� ����.
		for (int j = 0; j < n; j++)
		{
			if (score[j] == DEAD) continue;
			score[j] += r[i][j];
		}

		DayTime(playerNum - 1, nightCnt + 1); // ���� �Ǿ����ϴ�..
		memcpy(score, save, sizeof(int) * n); // ���� ����.
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &score[i]);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			scanf("%d", &r[i][j]);
	scanf("%d", &mafiaIdx);

	if (n % 2) DayTime(n, 0);
	else	   NightTime(n, 0);
	printf("%d", answer);

	return 0;
}