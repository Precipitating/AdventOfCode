#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include <vector>

using namespace std;


/* least common instead of most common (part 2) */
int main()
{
	fstream file; file.open("input.txt");
	string line;
	string finalString;
	vector<string> encryptedList(8);
	int idx = 0;

	/* parse each column into its own string in a vector */
	for (int i = 0; i < 8; ++i)
	{
		while (getline(file, line))
		{
			encryptedList[idx].append(string(1, line[idx]));

		}
		file.clear();
		file.seekg(0);
		++idx;
	}

	for (int i = 0; i < encryptedList.size(); ++i)
	{
		char largestChar;
		int charMatch = 99;
		for (int j = 0; j < encryptedList[i].size(); ++j)
		{
			char currentChar = encryptedList[i][j];
			regex currentCharFilter(string(1, currentChar));

			/* count all matches of current char */
			auto words_begin = sregex_iterator(encryptedList[i].begin(), encryptedList[i].end(), currentCharFilter);
			auto words_end = sregex_iterator();

			if (distance(words_begin, words_end) < charMatch)
			{
				charMatch = distance(words_begin, words_end);
				largestChar = encryptedList[i][j];

			}
		}
		finalString.append(string(1, largestChar));
	}






	return 0;
}