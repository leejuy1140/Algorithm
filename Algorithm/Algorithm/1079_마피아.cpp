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

	// 낮에 죽은 사람이 마피아거나 마피아만 남으면, 종료.
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

	int save[MAX]; // 현재 유죄 상태 저장.
	memcpy(save, score, sizeof(int) * n);
	
	// 죽일 사람 완전 탐색으로 선택.
	for (int i = 0; i < n; i++)
	{
		// 마피아 본인이거나 죽은 시민이면, 패스.
		if (i == mafiaIdx || score[i] == DEAD) continue;
		
		score[i] = DEAD; // 죽이고 유죄 상태 갱신.
		for (int j = 0; j < n; j++)
		{
			if (score[j] == DEAD) continue;
			score[j] += r[i][j];
		}

		DayTime(playerNum - 1, nightCnt + 1); // 낮이 되었습니다..
		memcpy(score, save, sizeof(int) * n); // 원상 복귀.
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