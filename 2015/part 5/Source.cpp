#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <array>

/* part 5 part 1*/

namespace fs = std::filesystem;

bool VowelDetector(const char&, const std::string& );
bool DisallowedDetector(const std::array<std::string, 4>&, const std::string&);

int main()
{
	int niceStrings = 0;
	const std::string filename = "input.txt";
	std::string line;
	std::string vowels = "aeiou";
	std::array<std::string, 4> disallowed = { "ab", "cd", "pq", "xy" };


	if (fs::exists(filename))
	{
		std::ifstream fileStream(filename);

		while (std::getline(fileStream, line))
		{
			/* ---------------------------------------------------------------------------------------- */
			/* if it contains these combinations of string, the line of input is automatically bad */

			if (DisallowedDetector(disallowed, line))
				continue;



			/* ---------------------------------------------------------------------------------------- */
			int vowelCount = 0;
			/* detect if we got 3 vowels, stop (find_if) if we have 3 vowels as condition is satisfied */
			std::find_if(line.begin(), line.end(), [vowels, &vowelCount](const char& currentChar)
				{
					bool isFinished = false;
					bool isCharVowel = VowelDetector(currentChar, vowels);

					if (isCharVowel && vowelCount < 3)
					{
						++vowelCount;
					}
					else if (vowelCount >= 3)
					{
						isFinished = true;
					}

					return isFinished;


				});

		//	std::cout << "Vowel in line: " << vowelCount << '\n';
			/* ---------------------------------------------------------------------------------------- */
			/* check if there are duplicates next to each other */
			bool hasDuplicates = false;
			for (auto it = line.begin(); it != line.end() - 1; ++it)
			{
				char x = *it;
				char y = *++it;
				if (x == y)
				{
					hasDuplicates = true;
				}

				/* undo the increment that  variable 'y' has done */
				--it;
			}


			/* no duplicates and has 3> values, its good*/
			if (hasDuplicates && vowelCount >= 3)
			{
				++niceStrings;
			}

		}




	}


	std::cout << niceStrings;
	return 0;
}



bool DisallowedDetector(const std::array<std::string, 4>& disallowed,const std::string& line)
{
	bool isDisallowed = false;

	for (const std::string& badPhrase : disallowed)
	{
		if (strstr(line.c_str(), badPhrase.c_str() ))
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