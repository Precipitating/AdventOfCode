#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

string ParseMarker(string& line, size_t nextPos, size_t &endBrackPos)
{
	string finalOutput;
	regex removeX("x");
	auto firstBrackPos = line.find_first_of("(", nextPos);
	auto closingBrackPos = line.find_first_of(")", nextPos);

	finalOutput = line.substr(firstBrackPos + 1, closingBrackPos - (firstBrackPos + 1));

	finalOutput = regex_replace(finalOutput, removeX, " ");

	string actualFinalString = finalOutput;
	for (int i = 0; i < closingBrackPos - firstBrackPos + 1; ++i)
	{
		line[firstBrackPos + i] = '*';
	}

	endBrackPos = closingBrackPos;
	return actualFinalString;


}

pair<string,size_t> GetStringToRepeat(int stringLength, const string& line, size_t endBracketPos)
{
	string finalOutput = line;

	finalOutput = finalOutput.substr(endBracketPos + 1, stringLength);

	size_t positionToRepeat = endBracketPos + (stringLength + 1);

	/* returns the string to repeat and position to repeat the string*/
	return make_pair(finalOutput,positionToRepeat);



}

int ProcessRepeat(string& line, pair<string, size_t> stringToRepeat, int timesToRepeat, size_t nextPos)
{
	string repeatedString;
	int nextBracketPos = stringToRepeat.second;
	for (int i = 0; i < timesToRepeat; ++i)
	{
		repeatedString.append(stringToRepeat.first);
		nextBracketPos += stringToRepeat.first.length();

	}


	line.insert(stringToRepeat.second, repeatedString);
	
	

	return (nextBracketPos);



}

void RemoveMarker(string& line, size_t currentPos)
{
	size_t firstBracketPos = line.find_first_of("(", currentPos);
	size_t endBracketPos = line.find_first_of(")", currentPos);

	line.erase(line.begin() + firstBracketPos, line.begin() + (endBracketPos + 1));

}


int main()
{
	fstream file; file.open("input.txt");
	string line;
	size_t nextPos = 0;


	while (getline(file, line))
	{
		string decompressed;

		while (line.find_first_of("(", nextPos ) != string::npos)
		{
			int dataLength = 0; int repeatLength = 0;
			size_t endBracketPos;
			pair<string,size_t> repeatString;


			/* parse the repeat length and data length values */
			string marker = ParseMarker(line, nextPos, endBracketPos);
			stringstream stream(marker);
			stream >> dataLength >> repeatLength;

			/* one instance of string to repeat already exists so -1 */
			--repeatLength;

			repeatString = GetStringToRepeat(dataLength, line, endBracketPos);

			/* start repeating it */
			nextPos = ProcessRepeat(line, repeatString, repeatLength, nextPos);
			//nextPos -= 4;

			//regex removeAstericks("*");
			//line = regex_replace(line, removeAstericks, "");
			//RemoveMarker(line, nextPos);


		}

		/* remove first marker as we've processed it */
		regex removeAsterisk("\\*");
		line = regex_replace(line, removeAsterisk, "");
		cout << line.length();


	}



	return 0;

}