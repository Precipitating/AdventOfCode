#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <regex>
#include <set>


using namespace std;

int countMatchInRegex(std::string s, std::string re)
{
	std::regex words_regex(re);
	auto words_begin = std::sregex_iterator(
		s.begin(), s.end(), words_regex);
	auto words_end = std::sregex_iterator();

	return std::distance(words_begin, words_end);
}

int main()
{
	fstream file; file.open("input.txt");
	string line;
	vector<string> seperatedStrings;
	char seperateChar = '-';
	int overallCheckSum = 0;

	while (getline(file, line))
	{
		

		/* seperate each string and put into vector*/
		string tempLine = line;

		size_t seperatedString = tempLine.find(seperateChar);

		while (seperatedString != std::string::npos)
		{
			tempLine = tempLine.substr(0, seperatedString);
			seperatedStrings.push_back(tempLine);
			line.erase(0,seperatedString + 1);

			tempLine = line;
			seperatedString = tempLine.find(seperateChar);
		}

		/* grab the sector ID incase its valid */
		stringstream stream(line);
		int sectorID;
		stream >> sectorID;

		/* remove number and square brackets from the input to get the common letters  */
		regex removeNumber("[\\d\\[\\]]");
		line = regex_replace(line, removeNumber, "");

		/* store common letters in a string */
		string inputCommonLetters = line;


		/* process similar characters */

		string concacenatedString;
		set <pair<char, int>> charCount;
		string correctCheckSum;
		
		/* put all the encrypted strings together without - */
		for (int i = 0; i < seperatedStrings.size(); ++i)
		{
			concacenatedString.append(seperatedStrings[i]);
		}

		/* get a count of each character and put in a set (set doesnt allow dupe chars) */
		for (int j = 0; j < concacenatedString.size(); ++j)
		{
			string currentChar{ concacenatedString[j] };

			int count = countMatchInRegex(concacenatedString, currentChar);

			charCount.insert(make_pair(concacenatedString[j], count));



		}
		
		/* get highest char count via a custom func due to pair usage */
		while (inputCommonLetters.size() > correctCheckSum.size())
		{
			auto maxNum = max_element(charCount.begin(), charCount.end(), [](const auto& lhs, const auto& rhs) {return lhs.second < rhs.second; });
			int cnt = count_if(charCount.begin(), charCount.end(), [&](const auto& pair) {return pair.second == maxNum->second; });
			set<pair<char, int>> orderedTieBreaker;

			/* append to correctCheckSum if the highest char count has no dupes*/
			if (cnt == 1)
			{
				string charConversion{ maxNum->first };
				correctCheckSum.append(charConversion);
				charCount.erase(maxNum);

			}
			else
			{
				/* if its a tie breaker, put in set and append to correctCheckSum, the set makes it automatically alphabetical in order */
				copy_if(charCount.begin(), charCount.end(), inserter(orderedTieBreaker, orderedTieBreaker.begin()), [&](const auto& pair) {return pair.second == maxNum->second; });

				for (const auto& pair : orderedTieBreaker)
				{
					if (inputCommonLetters.size() != correctCheckSum.size())
					{
						string charConversion{ pair.first };
						correctCheckSum.append(charConversion);
						charCount.erase(pair);
					}
					else
					{
						break;
					}


				}


				orderedTieBreaker.clear();
				seperatedStrings.clear();




			}
		}

		/* now compare correctCheckSum to the input checksum, if its the same then its valid, else no.*/

		if (correctCheckSum == inputCommonLetters)
		{
			overallCheckSum += sectorID;
		}

	}


	return 0;


}