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
	int part2Answer = 0;
	int nestCount = 0;
	bool garbageMode = false;
	while (getline(file, line))
	{
		stringstream stream(line);
		stream >> noskipws;
		char current;

		while (stream >> current)
		{
			if (!garbageMode)
			{
				switch (current)
				{
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
				default:
					++part2Answer;
				}
			}

		}
		//GetInnerBrackets(line, cancelRemover);


	}

	cout << part2Answer;


	return 0;

}