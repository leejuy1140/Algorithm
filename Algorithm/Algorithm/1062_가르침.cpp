#include <stdio.h>
#include <string.h>

const int N_MAX = 51;
const int LEN_MAX = 20;
const int ALPHA_MAX = 26;

int n, k, answer = 0;
char words[N_MAX][LEN_MAX];
int exist[ALPHA_MAX], learn[ALPHA_MAX];

void Teaching(int idx, int learnCnt)
{
	if (idx + k - 5 - learnCnt >= ALPHA_MAX) return;

	learn[idx] = 1;
	if (learnCnt == k - 5)
	{
		// 읽을 수 있는 단어의 개수 찾기.
		int readCnt = 0;
		for (int i = 0; i < n; i++)
		{
			int flag = 0; // 못 읽으면, 1.
			for (int j = 4; j < strlen(words[i]) - 4; j++)
			{
				if (!learn[words[i][j] - 'a'])
				{ flag = 1; break; }
			}
			if (!flag) readCnt++;
		}
		answer = readCnt > answer ? readCnt : answer;
		return;
	}

	for (int i = idx + 1; i < ALPHA_MAX; i++)
	{
		if (exist[i] && !learn[i])
		{
			Teaching(i, learnCnt + 1);
			learn[i] = 0;
		}
	}
}

int main()
{
	exist['a' - 'a'] = exist['n' - 'a'] = exist['t' - 'a'] = exist['i' - 'a'] = exist['c' - 'a'] = 1;
	learn['a' - 'a'] = learn['n' - 'a'] = learn['t' - 'a'] = learn['i' - 'a'] = learn['c' - 'a'] = 1;

	int alphaCnt = 0;
	scanf("%d %d", &n, &k);
	for(int i = 0; i < n; i++)
	{
		getchar();
		scanf("%s", &words[i]);
		for (int j = 4; j < strlen(words[i]) - 4; j++)
		{
			if (!exist[words[i][j] - 'a'])
			{
				exist[words[i][j] - 'a'] = 1;
				alphaCnt++;
			}
		}
	}
	if (alphaCnt <= k - 5)
	{
		printf("%d", n);
		return 0;
	}

	for (int i = 0; i < ALPHA_MAX; i++)
	{	
		if (exist[i] && !learn[i])
		{
			Teaching(i, 1);
			learn[i] = 0;
		}
	}
	printf("%d", answer);

	return 0;
}