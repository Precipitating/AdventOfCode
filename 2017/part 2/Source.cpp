#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;



int main()
{
	fstream file; file.open("input.txt");
	string line;
	int answer = 0;
	
	vector<int> row;
	while (getline(file, line))
	{
		int currentNum;

		stringstream stream(line);

		while (stream >> currentNum)
		{
			row.push_back(currentNum);

		}
		auto highestLow = minmax_element(row.begin(), row.end());

		int difference = *highestLow.second - *highestLow.first;

		answer += difference;


		row.clear();

	}

	cout << answer;

	return 0;
}