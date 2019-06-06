#include <string>
#include <vector>
#include <iostream>
using namespace std;

string solution(string start, string end)
{
	int start_hour = atoi(start.substr(3, 2).c_str());
	if (start[0] == 'P') start_hour += 12;
	int start_min = atoi(start.substr(6, 2).c_str());
	int start_sec = atoi(start.substr(9, 2).c_str());
	int start_time = (start_hour * 3600) + (start_min * 60) + start_sec;

	int end_hour = atoi(end.substr(3, 2).c_str());
	if (end[0] == 'P') end_hour += 12;
	int end_min = atoi(end.substr(6, 2).c_str());
	int end_sec = atoi(end.substr(9, 2).c_str());
	int end_time = (end_hour * 3600) + (end_min * 60) + end_sec;

	string answer;
	int gap_time = end_time - start_time;
	if (gap_time < 0) gap_time = 86400 + gap_time;

	int hour = gap_time / 3600;
	if (hour < 10) answer += '0';
	answer.append(to_string(hour));
	answer += ':';

	gap_time -= hour * 3600;
	int min = gap_time / 60;
	if (min < 10) answer += '0';
	answer.append(to_string(min));
	answer += ':';

	gap_time -= min * 60;
	if (gap_time < 10) answer += '0';
	answer.append(to_string(gap_time));

	return answer;
}