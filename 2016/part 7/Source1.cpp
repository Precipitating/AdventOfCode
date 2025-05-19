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
	regex pattern("((.).\\2)");
	regex samePattern("(.)\\1\\1");


	while (getline(file, line))
	{
		string extractedBracket = line;
		smatch matchPos;
		bool correctBracket = false;
		vector<string> potentialPatterns;

		/* search for ABA pattern in brackets */
		while (line.find_first_of("[") != string::npos)
		{
			auto first = extractedBracket.find_first_of("[");
			auto last = extractedBracket.find_first_of("]");

			extractedBracket = extractedBracket.substr(first + 1, last - (first + 1));


			while (regex_search(extractedBracket, matchPos, pattern))
			{
				correctBracket = true;
				potentialPatterns.push_back(extractedBracket.substr(matchPos.position(), 3));
				extractedBracket.erase(matchPos.position(), 3);
			}
			line[first] = '*';
			line[last] = '*';

			line.erase(first + 1, last - (first + 1));

			extractedBracket = line;


		}

		bool matchFound = false;
		if (correctBracket)
		{
			int idx = 0;
			int end = 3;
			while (idx + 3 <= line.length())
			{
				string currentMatchCheck = line.substr(idx, end);

				for (int i = 0; i < potentialPatterns.size(); ++i)
				{
					string swapped;

					swapped.append(string(1, potentialPatterns[i][1])); swapped.append(string(1, potentialPatterns[i][0])); swapped.append(string(1, potentialPatterns[i][1]));

					if (currentMatchCheck == swapped)
					{
						if (!regex_search(swapped, samePattern))
						{
							matchFound = true;
							break;
						}
						else
						{
							cout << "dupe";
						}
					}


				}
				++idx;
			}





			if (matchFound)
			{
				++supportedIps;
			}


		}




	}

	std::cout << supportedIps;
	return 0;

}

//#include <iostream>
//#include <string>
//#include <set>
//#include <fstream>
//
//
//int main()
//{
//	int count = 0;
//	std::fstream file; file.open("input.txt");
//	std::string line;
//	while (std::getline(file,line))
//	{
//		std::set<std::pair<char, char>> aba, bab;
//		bool hyper = false;
//		for (const char* p = line.c_str(); p[2] != '\0'; ++p) 
//		{
//			if (*p == '[')
//			{
//				hyper = true;
//			}
//			else if (*p == ']') 
//			{ 
//				hyper = false;
//			}
//			else if (p[0] == p[2] && p[0] != p[1])
//			{
//				if (hyper) 
//				{
//					bab.insert({ p[1], p[0] }); 
//				}
//				else { aba.insert({ p[0], p[1] }); }
//			}
//		}
//		for (auto ab : aba) {
//			if (bab.find(ab) != bab.end()) {
//				++count; break;
//			}
//		}
//	}
//	std::cout << count << std::endl;
//
//	return 0;
//}