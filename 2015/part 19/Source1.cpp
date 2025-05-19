#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>
#include <map>
#include <unordered_map>
#include <set>
#include <ctime>
#include <algorithm>
#include <random>

using namespace std;

/* now we want to start the input at "e" and figure out how many steps it takes to reach the callibrationInput*/
/* going through the rules one by one */
int main()
{
	auto rng = default_random_engine{};
	fstream file;
	file.open("input.txt");
	string line;
	regex removeArrow("=>");
	string callibrationInput;
	string start;
	unordered_multimap<string, string> keys;


	int callibrationFlag = 0;
	while (getline(file, line))
	{

		if (callibrationFlag == 1)
		{
			callibrationInput.append(line);
		}

		if (!line.empty() && callibrationFlag != 1)
		{
			string key, value;
			line = regex_replace(line, removeArrow, "");
			stringstream stream(line);

			stream >> key >> value;

			keys.insert(make_pair(value, key));



		}
		else
		{
			callibrationFlag = 1;
		}

	}





	set<string> uniqueCombos;
	string tempCallibration = callibrationInput;
	int steps = 0;
	bool keepGoing = true;

	while (tempCallibration != "e")
	{
		std::cout << tempCallibration << '\n';
		int noMatch = 0;

		for (auto it = keys.begin(); it != keys.end(); ++it)
		{
			regex currentKey(it->first);

			// Counting the number of replacements
			size_t count = std::distance(
				sregex_iterator(tempCallibration.begin(), tempCallibration.end(), currentKey),
				sregex_iterator());

			if (count > 0)
			{
				tempCallibration = regex_replace(tempCallibration, currentKey, it->second, regex_constants::format_first_only);
				++steps;
				break;
			}
			else
			{
				++noMatch;
			}

		}



		if (noMatch == keys.size())
		{
			vector<pair<string, string>> shuffleVec; 
			for (auto it3 = keys.begin(); it3 != keys.end(); ++it3)
			{
				shuffleVec.push_back(make_pair(it3->first, it3->second));
			}

			shuffle(shuffleVec.begin(), shuffleVec.end(), rng);

			keys.clear();

			for (int i = 0; i < shuffleVec.size(); ++i)
			{
				keys.insert(shuffleVec[i]);
			}

			tempCallibration = callibrationInput;
			steps = 0;
			/* dead end.. lets shuffle and reset it*/


		}

	}
	

	std::cout << steps;


	return 0;


}

