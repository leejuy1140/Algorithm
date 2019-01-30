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
		// 따로 덧셈을 하지 않아도 됨
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
	
	// 기저 1. 자리 수를 나누기 위해, 자리수가 긴 쪽을 a로 설정.
	if (a_len < b_len) return karatsuba(b, a);

	// 기저 2. 길이 50이하는 일반적인 빠른 곱셈으로 처리.
	// 여기서 
	if (a_len <= 50) multiply(a, b);

	// 1. a0, a1 / b0, b1을 위한 공간 할당
	int half = a_len / 2;
	
	vector<char> a0(a.begin(), a.begin() + half);
	vector<char> a1(a.begin() + half, a.end());
	
	vector<char> b0(b.begin(), b.begin() + min(half, b_len));
	vector<char> b1(b.begin() + min(half, b_len), b.end());

	// 2. z0, z1, z2는 다 곱셈이기 때문에, 카라츠바로 구하기
	vector<int> z0 = karatsuba

}

int main()
{
	scanf("%s %s", &num1[0], &num2[0]);

	// 자리수 나누기 & 3개의 곱셈으로 분할하는 함수
	karatsuba(num1, num2);


	

	return 0;
}