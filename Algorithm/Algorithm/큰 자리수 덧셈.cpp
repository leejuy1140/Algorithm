#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;

void swapString(char *str1, char *str2)
{
	char tmp[105];
	strcpy(tmp, str1);
	strcpy(str1, str2);
	strcpy(str2, tmp);
}

int main() {

	//Please Enter Your Code Here
	char str1[105], str2[105];
	scanf("%s %s", str1, str2);

	// 큰 수를 str1, 작은 수를 str2로 설정
	if (strlen(str1) == strlen(str2))
	{
		if (strcmp(str1, str2) < 0)
			swapString(str1, str2);
	}
	else if (strlen(str1) < strlen(str2))
		swapString(str1, str2);

	int i = strlen(str1) - 1;
	int j = strlen(str2) - 1;

	int r = i + 1;  // 결과 배열의 마지막 인덱스 (0번은 오버플로우 자리)
	int s = r + 1;	// 결과 배열 크기
	vector<char> result(s); // 결과 배열

	while (1)
	{
		if (i < 0)	break;

		int sum;
		if (j < 0) sum = str1[i] - '0' + result[r];
		else			 sum = str1[i] - '0' + str2[j] - '0' + result[r];

		if (sum > 9)
		{
			result[r] = (sum % 10);
			result[r - 1]++;
		}
		else result[r] = sum;

		i--; j--; r--;
	}

	for (int i = 0; i < s; i++)
	{
		if (i == 0 && result[i] == 0) continue;
		printf("%d", result[i]);
	}

	return 0;
}