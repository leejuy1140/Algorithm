#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

bool isUpper(char c)
{
	return (c >= 'A') && (c <= 'Z');
}

bool compare(pair<int, int> a, pair<int, int> b)
{
	if (a.second > b.second) return false;
	else if (a.second == b.second)
	{
		if (a.first < b.first) return false;
		else return true;
	}
	else return true;
}

string solution(string s)
{
	pair<char, int> cnt[26]; // 알파벳 카운팅 배열.
	for (int i = 0; i < 26; i++)
	{
		cnt[i].first = i + 'a'; // 어떤 알파벳인지.
		cnt[i].second = 0; // 해당 알파벳이 몇 개인지.
	}

	for (int i = 0; i < s.size(); i++) // 카운팅.
	{
		if (isUpper(s[i])) cnt[s[i] - 'A'].second++;
		else			   cnt[s[i] - 'a'].second++;
	}

	sort(&cnt[0], &cnt[26], compare); // 정렬.

	string answer;
	answer += cnt[25].first;
	for (int i = 24; i >= 0; i--)
	{
		if (cnt[i].second == cnt[i + 1].second) answer += cnt[i].first;
		else break;
	}
	return answer;
}

int main()
{
	string input;
	cin >> input;
	cout << solution(input);
}