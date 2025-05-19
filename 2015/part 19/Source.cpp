#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>
#include <map>
#include <set>

using namespace std;


int main()
{
	fstream file;
	file.open("input.txt");
	string line;
	regex removeArrow("=>");
	string callibrationInput;
	multimap<string, string> keys;


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

			keys.insert(make_pair(key, value));



		}
		else
		{
			callibrationFlag = 1;
		}

	}

	set<string> uniqueCombos;
	for (auto it = keys.begin(); it != keys.end(); ++it)
	{
		string tempCallibration = callibrationInput;
		regex currentKey(it->first);

		// Counting the number of replacements
		size_t count = std::distance(
				sregex_iterator(tempCallibration.begin(), tempCallibration.end(), currentKey),
				sregex_iterator()
		);

		auto begin = sregex_iterator{ callibrationInput.begin(), callibrationInput.end(), currentKey };
		auto end = sregex_iterator();

		/* for each regex match, replace that with the keys values and place it in a set, which contains unique combinations.*/
		for (std::sregex_iterator i = begin; i != end; ++i)
		{
			string::const_iterator matchPosition = tempCallibration.begin() + i->position();
			string::const_iterator replaceLength = tempCallibration.begin() + i->position() + i->length();

			tempCallibration.replace(matchPosition, replaceLength, it->second);


			uniqueCombos.insert(tempCallibration);
			tempCallibration = callibrationInput;

		}




	}

	std::cout << uniqueCombos.size();



	return 0;


}

