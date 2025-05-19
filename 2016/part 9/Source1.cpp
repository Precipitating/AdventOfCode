#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

string ParseMarker(string& line, size_t& endBrackPos)
{
	string finalOutput;
	regex removeX("x");
	auto firstBrackPos = line.find_first_of("(");
	auto closingBrackPos = line.find_first_of(")" );

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

pair<string, size_t> GetStringToRepeat(int stringLength, const string& line, size_t endBracketPos)
{
	string finalOutput = line;

	finalOutput = finalOutput.substr(endBracketPos + 1, stringLength);

	size_t positionToRepeat = endBracketPos + (stringLength + 1);

	/* returns the string to repeat and position to repeat the string*/
	return make_pair(finalOutput, positionToRepeat);



}

int ProcessRepeat(string& line, pair<string, size_t> stringToRepeat, int timesToRepeat)
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
	long long count = 0;

	while (getline(file, line))
	{
		vector<int> weights(line.size(), 1);
		string decompressed;

		for (int i = 0; i < line.size(); ++i)
		{

			if (line[i] != '(' )
			{ 
				count += weights[i];

			}
			else
			{
				/* process marker */
				int dataLength = 0; int repeatLength = 0;
				size_t endBracketPos;
				string marker = ParseMarker(line, endBracketPos);
				stringstream stream(marker);
				stream >> dataLength >> repeatLength;

				for (int j = 0; j < dataLength; ++j)
				{
					weights[endBracketPos + 1 + j] *= repeatLength;
				}

				i = endBracketPos;
			}


		}
	}

	cout << count;
	return 0;

}