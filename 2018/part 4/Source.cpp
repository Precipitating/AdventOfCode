#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

#pragma region PART 1
//int main()
//{
//	fstream file; file.open("input.txt");
//	string line;
//	vector<string> schedule;
//	map<int, int> mappedSleep;
//	map<int, map<int,int>> commonSleepTime;
//	schedule.reserve(1086);
//	int currGuard;
//	int startTimeAsleep = 0;
//	int endTimeAsleep = 0;
//
//	while (getline(file, line))
//	{
//		schedule.push_back(line);
//	}
//
//	sort(schedule.begin(), schedule.end());
//
//	for (const string& s : schedule)
//	{
//		int start = s.find('#');
//		int end = s.find(' ', start);
//
//		if (start != string::npos)
//		{
//			++start;
//			currGuard = stoi(s.substr(start, end - start));
//
//		}
//		else if (s.find("asleep") != string::npos)
//		{
//			startTimeAsleep = stoi(s.substr(15, 2));
//		}
//		else if (s.find("wakes") != string::npos)
//		{
//			endTimeAsleep = stoi(s.substr(15, 2));
//			mappedSleep[currGuard] += endTimeAsleep - startTimeAsleep;
//
//			for (int i = startTimeAsleep; i < endTimeAsleep; ++i)
//			{
//				++commonSleepTime[currGuard][i];
//			}
//			startTimeAsleep = 0;
//			endTimeAsleep = 0;
//		}
//	}
//
//	auto maxElem = max_element(mappedSleep.begin(), mappedSleep.end(), [](const auto& a, const auto& b) {return a.second < b.second; });
//	auto bestTime = max_element(commonSleepTime[maxElem->first].begin(), commonSleepTime[maxElem->first].end(), [](const auto& a, const auto& b) {return a.second < b.second; });
//	return maxElem->first * bestTime->first;
//}
#pragma endregion


#pragma region PART 2 
int main()
{
	fstream file; file.open("input.txt");
	string line;
	vector<string> schedule;
	map<int, int> mappedSleep;
	map<int, map<int, int>> commonSleepTime;
	schedule.reserve(1086);
	int currGuard;
	int startTimeAsleep = 0;
	int endTimeAsleep = 0;

	while (getline(file, line))
	{
		schedule.push_back(line);
	}

	sort(schedule.begin(), schedule.end());

	for (const string& s : schedule)
	{
		int start = s.find('#');
		int end = s.find(' ', start);

		if (start != string::npos)
		{
			++start;
			currGuard = stoi(s.substr(start, end - start));

		}
		else if (s.find("asleep") != string::npos)
		{
			startTimeAsleep = stoi(s.substr(15, 2));
		}
		else if (s.find("wakes") != string::npos)
		{
			endTimeAsleep = stoi(s.substr(15, 2));
			mappedSleep[currGuard] += endTimeAsleep - startTimeAsleep;

			for (int i = startTimeAsleep; i < endTimeAsleep; ++i)
			{
				++commonSleepTime[currGuard][i];
			}
			startTimeAsleep = 0;
			endTimeAsleep = 0;
		}
	}

	pair<int, int> frequentSleeper{ 0,0 };
	int bestMin = 0;
	for (const auto& [key, value] : commonSleepTime)
	{
		auto bestTime = max_element(commonSleepTime[key].begin(), commonSleepTime[key].end(), [](const auto& a, const auto& b) {return a.second < b.second; });

		if (bestTime->second > bestMin)
		{
			frequentSleeper = { key, bestTime->first };
			bestMin = bestTime->second;
		}
	}

	return frequentSleeper.first * frequentSleeper.second;
}
#pragma endregion