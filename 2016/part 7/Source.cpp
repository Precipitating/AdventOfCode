#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include <vector>

using namespace std;


int main()
{
	fstream file; file.open("input.txt");
	int supportedIps = 0;
	string line;
	regex pattern(R"(([a-z])((?!\1)[a-z])\2\1)");
	regex samePattern(R"((.)\1{3})");


	while (getline(file, line))
	{
		string extractedBracket = line;
		smatch matchPos;
		bool correctBracket = true;

		/* search for ABBA pattern in brackets */
		size_t nextBracket = 0;
		while (line.find_first_of("[", nextBracket) != string::npos)
		{
			auto first = extractedBracket.find_first_of("[", nextBracket);
			auto last = extractedBracket.find_first_of("]", nextBracket);

			extractedBracket = extractedBracket.substr(first + 1, last - (first + 1));

		
			if (regex_search(extractedBracket, pattern))
			{
				correctBracket = false;
			}


			nextBracket = last + 1;
			//line.erase(first + 1 , last - (first + 1));

			extractedBracket = line;

		}


		if (correctBracket)
		{
			if (regex_search(line, matchPos, pattern))
			{
				bool allCharSame = false;
				string currentMatch = line.substr(matchPos.position(), 4);

				if (regex_match(currentMatch,samePattern))
				{
					allCharSame = true;
				}
				else
				{
					allCharSame = false;
				}

				if (!allCharSame)
				{
					++supportedIps;
					//break;
				}


				//line.erase(matchPos.position(), 4);


			}


		}
		



	}

	std::cout << supportedIps;
	return 0;

}