#include <iostream>
#include <fstream>
#include <string>
#include<iomanip>
#include <algorithm>
#include <regex>


int main()
{

	std::ifstream file;

	file.open("input.txt");
	std::string line;
	int charCount = 0;
	int literalCount = 0;

	std::regex memquotes("^\"|\"$");
	std::regex doubleslash("\\\\\\\\");
	std::regex asciihex("\\\\x[a-zA-Z0-9]{2}");
	std::regex actualquotes("\\\\\"");



	while (getline(file, line))
	{

		charCount += line.size();

	}

	file.clear();
	file.seekg(0);






	while (getline(file, line))
	{

		/*line.erase(0, 1);
		line.erase(line.size() - 1, 1);*/
		line = std::regex_replace(line, memquotes, "");
		line = std::regex_replace(line, doubleslash, "*");
		line = std::regex_replace(line, asciihex, "*");
		line = std::regex_replace(line, actualquotes, "*");


		
	//	line = std::regex_replace(line, hexRegex1, "");

		literalCount += line.size();
		/*for (int i = 0; i < line.size(); ++i)
		{


			if (line[i] == '\\')
			{

				if (line[i + 1] == '\\')
				{
					++literalCount;
				}
				else
				{
					++literalCount;
				}


			}
			else if (line[i] == '\"')
			{
				continue;
			}
			else
			{
				++literalCount;
			}

		}*/


	}
	//std::cout << literalCount;
	int answer = charCount - literalCount;
	std::cout << answer;






	return 0;
}