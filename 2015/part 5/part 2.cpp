#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <array>
#include <string_view>


/* part 5 part 1*/

namespace fs = std::filesystem;

bool VowelDetector(const char&, const std::string&);
bool DisallowedDetector(const std::array<std::string, 4>&, const std::string&);

int main()
{
	int niceStrings = 0;
	const std::string filename = "input.txt";
	std::string line;
	std::array<std::string, 4> disallowed = { "ab", "cd", "pq", "xy" };


	if (fs::exists(filename))
	{
		std::ifstream fileStream(filename);

		while (std::getline(fileStream, line))
		{

			/* ---------------------------------------------------------------------------------------- */
			/* if it contains these combinations of string, the line of input is automatically bad */

			//if (DisallowedDetector(disallowed, line))
			//	continue;



			/* ---------------------------------------------------------------------------------------- */

			/* check if it contains at least one letter which repeats with exactly one letter between them next to each other */
			bool hasDuplicates = false;
		//	std::vector<std::pair<char, char>> vecPairs;
			//for (auto it = line.begin(); it != line.end() - 1; ++it)
			//{
			//	char x = *it;
			//	std::advance(it, 1);
			//	char y = *it;

			//	vecPairs.push_back(std::make_pair(x, y));

			//	std::advance(it, -1);
			//}

			for (size_t i = 0; i < line.size() - 2; ++i)
			{
				std::string_view str_toSearch(&line[i], 2); // The first 2 elements of the string
				std::string_view str_toSearchIn(&line[i + 2], line.size() - i - 2); // The rest of the string
				if (str_toSearchIn.find(str_toSearch) != std::string_view::npos)
				{
					hasDuplicates = true;
				}
			}

			bool hasRepeat = false;


			for (size_t i = 0; i < line.size() - 2; ++i)
			{
				if (line[i] == line[i + 2]) { hasRepeat = true; }
 			}


			

			//std::sort(vecPairs.begin(), vecPairs.end());
			//hasDuplicates = std::adjacent_find(vecPairs.begin(), vecPairs.end()) != vecPairs.end();


			/* no duplicates and has 3> values, its good*/
			if (hasDuplicates && hasRepeat)
			{
				++niceStrings;
			}

		}




	}


	std::cout << niceStrings;
	return 0;
}



bool DisallowedDetector(const std::array<std::string, 4>& disallowed, const std::string& line)
{
	bool isDisallowed = false;

	for (const std::string& badPhrase : disallowed)
	{
		if (strstr(line.c_str(), badPhrase.c_str()))
		{
			isDisallowed = true;
			break;
		}
	}


	return isDisallowed;


}

bool VowelDetector(const char& currentChar, const std::string& vowels)
{
	bool result = false;
	int vowelCount = 0;

	for (auto it = vowels.begin(); it != vowels.end(); ++it)
	{
		if (*it == currentChar)
		{
			++vowelCount;
		}
	}

	if (vowelCount > 0)
	{
		result = true;
	}



	return result;
}