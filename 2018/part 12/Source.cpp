#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

int main()
{
	fstream file("input.txt");
	string line;
	bool initialDone = false;
	unordered_map<string, char> keys;

	string initialState;

	while (getline(file, line))
	{
		if (line == "") continue;
		if (!initialDone)
		{
			initialState = line.substr(line.rfind(" ") + 1);
			initialDone = true;
		}
		else
		{
			string key = line.substr(0, 5);
			char result = line[line.size() - 1];
			keys[key] = result;

		}


	}

	int padSize = 1000;
	initialState = string(padSize,'.') + initialState + string(padSize, '.');

	string currSubstr;

	int lastResult = 0;
	int difference = INT_MIN;
	int tolerance = 0;
	long long actualResult = 0;

	for (size_t gen = 0; gen < 200; ++gen)
	{
		string next = initialState;
		for (size_t j = 2; j < next.size() - 2; ++j)
		{
			currSubstr = initialState.substr(j - 2, 5);
			next[j] = keys.count(currSubstr) ? keys[currSubstr] : '.';


		}
		initialState = next;

		int result = 0;
		for (size_t i = 0; i < initialState.size(); ++i)
		{
			if (initialState[i] == '#')
			{
				result += i - padSize;
			}
		}
		int currDiff = result - lastResult;
		lastResult = result;

		if (currDiff == difference)
		{
			++tolerance;
			if (tolerance >= 10)
			{
				actualResult = result + ((50000000000LL - gen) * currDiff);
				// one off error correction
				actualResult -= currDiff;
				break;
			}

		}
		else
		{
			tolerance = 0;
		}

		difference = currDiff;

	}


	std::cout << actualResult;



	return 0;

}