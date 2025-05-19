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
	std::regex singleslash("\\\\");
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
		std::string a = "***";
		std::string b = "^^^^";
		line = std::regex_replace(line, memquotes, a);
		line = std::regex_replace(line, actualquotes, b);

		line = std::regex_replace(line, singleslash, "--");
		line = std::regex_replace(line, doubleslash, "----");
		//line = std::regex_replace(line, asciihex, "*");
		//line = std::regex_replace(line, actualquotes, "*");



		//	line = std::regex_replace(line, hexRegex1, "");

		literalCount += line.size();




	}
	//std::cout << literalCount;
	
	int answer = literalCount - charCount;
	std::cout << answer;






	return 0;
}