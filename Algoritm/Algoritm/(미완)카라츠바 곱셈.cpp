#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 1000;

vector<char> num1(MAX), num2(MAX);

void multiply() // O(n^2)
{
	result = (int *)malloc(sizeof(int) * resultSize);
	memset(result, 0, sizeof(int) * resultSize);

	for (int i = 0; i < strlen(num1); i++)
	{
		// ���� ������ ���� �ʾƵ� ��
		for (int j = 0; j < strlen(num2); j++)
			result[i + j] += (num1[i] - '0') * (num2[j] - '0');
	}
}

void normalization()
{
	for (int i = 0; i < resultSize; i++) // O(n)
	{
		result[i + 1] += result[i] / 10;
		result[i] %= 10;
	}
}

void karatsuba(vector<char> a, vector<char> b)
{
	int a_len = a.size();
	int b_len = b.size();
	
	// ���� 1. �ڸ� ���� ������ ����, �ڸ����� �� ���� a�� ����.
	if (a_len < b_len) return karatsuba(b, a);

	// ���� 2. ���� 50���ϴ� �Ϲ����� ���� �������� ó��.
	// ���⼭ 
	if (a_len <= 50) multiply(a, b);

	// 1. a0, a1 / b0, b1�� ���� ���� �Ҵ�
	int half = a_len / 2;
	
	vector<char> a0(a.begin(), a.begin() + half);
	vector<char> a1(a.begin() + half, a.end());
	
	vector<char> b0(b.begin(), b.begin() + min(half, b_len));
	vector<char> b1(b.begin() + min(half, b_len), b.end());

	// 2. z0, z1, z2�� �� �����̱� ������, ī�����ٷ� ���ϱ�
	vector<int> z0 = karatsuba

}

int main()
{
	scanf("%s %s", &num1[0], &num2[0]);

	// �ڸ��� ������ & 3���� �������� �����ϴ� �Լ�
	karatsuba(num1, num2);


	

	return 0;
}