#include <iostream>
#include <regex>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include "json.hpp"
using json = nlohmann::json;



void RedRemover(std::string& input)
{
	bool finished = false;
	std::string tempInput = input;
	std::vector<std::pair<size_t, size_t>> redPositions;

	while (tempInput.find_last_of('{') != std::string::npos)
	{
		std::string temp;
		/* extract the last curly bracket pair and add positions to vector if  "red" found to delete at end*/
		size_t startBracket = tempInput.find_last_of('{');
		temp = tempInput.substr(startBracket, tempInput.length());
		size_t endBracket = temp.find_first_of('}');
		temp = temp.substr(0, endBracket);

		if (temp.find("red") != -1)
		{
			input.erase(startBracket, endBracket);

		}

		tempInput.erase(startBracket, endBracket);







	}
}


int getSum(json& data)
{

	auto sum =  0;

	for (const auto& [key, value] : data.items())
	{


		if (value.is_number())
		{
			sum += value.get<int>();
		}
		else if (value.is_array() || value.is_object())
		{
			sum += getSum(value);
		}
		else if (data.is_object() && value.is_string())
		{
			if (value.get<std::string>() == "red")
			{
				sum = 0;
				break;
			}

		}


	}
	return sum;



}
int main()
{
	//std::fstream file;
	std::regex numDetect("[^\\d-]+");
	


	int addedNum = 0;

	std::ifstream file("input.txt");

	//std::string input;

	json data = json::parse(file);

	addedNum = getSum(data);


	/*while (getline(file, input))
	{
		RedRemover(input);

		RedRemover(input);
		input = std::regex_replace(input, numDetect, " ");
		std::stringstream stream(input);

		while (!stream.eof())
		{
			int num;

			stream >> num;

			addedNum += num;

		}





	}*/


	std::cout << addedNum;





}