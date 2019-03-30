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

	// ū ���� str1, ���� ���� str2�� ����
	int sign = 0; // ��ȣ�� +�� 0, -�� 1
	if (strlen(str1) == strlen(str2))
	{
		if (strcmp(str1, str2) < 0)
		{
			swapString(str1, str2);
			sign = 1;
		}
	}
	else if (strlen(str1) < strlen(str2))
	{
		swapString(str1, str2);
		sign = 1;
	}
	if (sign) printf("-");

	int i = strlen(str1) - 1;
	int j = strlen(str2) - 1;
	int s = i + 1;		        // ��� �迭 ũ�� (carry ����)
	vector<int> result(s, 0); // ��� �迭

	while (1)
	{
		if (i < 0)	break;

		int minus;
		if (j < 0) minus = (str1[i] - '0') + result[i];
		else	     minus = (str1[i] - '0') - (str2[j] - '0') + result[i];

		if (minus < 0)
		{
			result[i - 1]--;
			result[i] = 10 + minus;
		}
		else result[i] = minus;

		i--; j--;
	}

	int flag = 0;
	for (int i = 0; i < s; i++)
	{
		if (result[i] != 0) flag = 1;
		if (flag) printf("%d", result[i]);
	}
	if (!flag) printf("0");

	return 0;
}