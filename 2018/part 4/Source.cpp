#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;


int main()
{
	fstream file; file.open("input.txt");
	string line;
	vector<string> schedule;
	map<int, int> mappedSleep;
	schedule.reserve(1086);

	while (getline(file, line))
	{
		schedule.push_back(line);
	}

	sort(schedule.begin(), schedule.end());
	return 0;
}