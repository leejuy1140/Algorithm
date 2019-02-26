#include <stdio.h>

struct Gear { int status[8]; };
Gear gear[5];

/* _gearNum¹ø Åé´Ï¹ÙÄû¸¦ µ¹¸®°ÔµÇ¸é, µ¹¾Æ°¡´Â Åé´Ï¹ÙÄû Ã¼Å©. */
void chkRotation(int _rotate[], int _gearNum, bool isLeft)
{
	if (isLeft) {
		for (int i = _gearNum - 1; i >= 1; i--)
		{
			if (gear[i + 1].status[6] != gear[i].status[2])
				_rotate[i] = _rotate[i + 1] * (-1);
			else break;
		}
	}
	else {
		for (int i = _gearNum + 1; i <= 4; i++)
		{
			if (gear[i - 1].status[2] != gear[i].status[6])
				_rotate[i] = _rotate[i - 1] * (-1);
			else break;
		}
	}
}

/* g¹ø Åé´Ï¹ÙÄû¸¦ dir¹æÇâÀ¸·Î È¸Àü. */
void doRotate(int g, int dir)
{
	if (dir == 1) {
		int back = gear[g].status[7];
		for (int i = 7; i >= 1; i--)
			gear[g].status[i] = gear[g].status[i - 1];
		gear[g].status[0] = back;
	}
	else {
		int front = gear[g].status[0];
		for (int i = 0; i <= 6; i++)
			gear[g].status[i] = gear[g].status[i + 1];
		gear[g].status[7] = front;
	}
}

int main()
{
	for (int i = 1; i <= 4; i++)
		for (int j = 0; j < 8; j++)
			scanf("%1d", &(gear[i].status[j]));
	int k; scanf("%d", &k);

	for (int i = 0; i < k; i++)
	{
		int gearNum, rotDir;
		scanf("%d %d", &gearNum, &rotDir);

		// Åé´Ï¹ÙÄû°¡ µ¹¾Æ¾ßÇÏ´Â ¹æÇâ ¼³Á¤.
		int rotate[5] = { 0, 0, 0, 0, 0 };
		rotate[gearNum] = rotDir;
		chkRotation(rotate, gearNum, 0);
		chkRotation(rotate, gearNum, 1);
		
		// Åé´Ï¹ÙÄû¸¦ µ¹¸².
		for (int j = 1; j <= 4; j++) {
			if (rotate[j] == 1)  doRotate(j, 1);
			if (rotate[j] == -1) doRotate(j, -1);
		}
	}

	int answer = 0;
	if (gear[1].status[0]) answer += 1;
	if (gear[2].status[0]) answer += 2;
	if (gear[3].status[0]) answer += 4;
	if (gear[4].status[0]) answer += 8;
	printf("%d\n", answer);

	return 0;
}