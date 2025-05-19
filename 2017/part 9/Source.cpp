#include <iostream>
#include <sstream>
#include <regex>
#include <string>
#include <fstream>

using namespace std;

int main()
{
	fstream file; file.open("input.txt");
	string line;
	regex cancelRemover("!(.)");
	int part1Answer = 0;
	int nestCount = 0;
	bool garbageMode = false;
	while (getline(file, line))
	{
		stringstream stream(line);
		char current;

		while (stream >> current)
		{
			if (!garbageMode)
			{
				switch (current)
				{
				case '{':
					++nestCount;
					break;
				case '}':
					part1Answer += nestCount;
					--nestCount;
					break;
				case '<':
					garbageMode = true;
					break;
				}
			}
			else
			{
				switch (current)
				{
				case '!':
					stream.ignore(1);
					break;
				case '>':
					garbageMode = false;
					break;
				}
			}

		}
		//GetInnerBrackets(line, cancelRemover);


	}

	cout << part1Answer;


	return 0;

}