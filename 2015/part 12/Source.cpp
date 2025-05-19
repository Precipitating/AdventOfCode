#include <iostream>
#include <regex>
#include <fstream>
#include <sstream>
#include <string>

int main()
{
	std::fstream file;
	std::regex numDetect("[^\\d-]+");
	int addedNum = 0;
	file.open("input.txt");

	std::string input;


	while (getline(file, input))
	{


		input = std::regex_replace(input, numDetect, " ");
		std::stringstream stream(input);

		while (!stream.eof())
		{
			int num;

			stream >> num;

			addedNum += num;

		}





	}


	std::cout << addedNum;





}