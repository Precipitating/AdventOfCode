#include <iostream>
#include <vector>
#include <array>
#include <fstream>
#include <string_view>
#include <string>
#include <utility>
#include <algorithm>
#include <sstream>



void HandleToggle(std::vector<std::array<int, 1000>>& grid, const std::pair<int, int>& start, const std::pair<int, int>& end)
{

	for (size_t i = start.second; i <= end.second; ++i)
	{
		for (size_t j = start.first; j < end.first + 1; ++j)
		{
			grid[i][j] = !(grid[i][j]);
		}



	}


}
void HandleTurnOnOff(int type, std::vector<std::array<int, 1000>>& grid, const std::pair<int, int>& start, const std::pair<int, int>& end)
{
	/*
		2 = on
		3 = off
	*/

	switch (type)
	{
	case 2:
	{
		for (size_t i = start.second; i <= end.second; ++i)
		{
			for (size_t j = start.first; j < end.first + 1; ++j)
			{
				grid[i][j] = 1;
			}

		}
	}
		break;
	case 3:
	{
		for (size_t i = start.second; i <= end.second; ++i)
		{
			for (size_t j = start.first; j < end.first + 1; ++j)
			{
				grid[i][j] = 0;
			}

		}
	}
		break;
	}
}

void RemoveWordFromLine(std::string& line, const std::string& word)
{
	auto n = line.find(word);
	if (n != std::string::npos)
	{
		line.erase(n, word.length());
	}
}

void extractRanges(std::pair<int, int>& start, std::pair<int, int>& end, const std::string& data, const std::string& noPhrase)
{
	
	std::string strippedData = data;

	/* remove the fluff */
	RemoveWordFromLine(strippedData, noPhrase);
	RemoveWordFromLine(strippedData, "through");
	RemoveWordFromLine(strippedData, " ");
	
	/* space numbers out so stringstream can nicely extract them into our range variables */
	for (size_t i = 0; i < strippedData.length(); ++i)
	{
		if (strippedData[i] == ',')
		{
			strippedData[i] = ' ';
		}
	}

	std::stringstream stream(strippedData);
	stream >> start.first >> start.second >> end.first >> end.second;

	


}


int main()
{
	std::vector<std::array<int, 1000>> grid(1000);

	std::ifstream file;
	std::pair<std::string, int> cmd[3] = { std::make_pair("toggle", 1), std::make_pair("turn on", 2),std::make_pair("turn off", 3) };
	std::string line;
	file.open("input.txt");


	while (getline(file, line))
	{
		std::pair<int, int> startRange;
		std::pair<int, int> endRange;

		for (const auto& command : cmd)
		{


			if (strstr(line.c_str(), command.first.c_str()))
			{
				switch (command.second)
				{

				case 1:
					extractRanges(startRange, endRange, line, command.first);
					HandleToggle(grid, startRange, endRange);
					break;
				case 2:
				case 3:
					extractRanges(startRange, endRange, line, command.first);
					HandleTurnOnOff(command.second,grid, startRange, endRange);
					break;
				}
				break;
			}
		}
		
	}

	int count = 0;
	for (const auto& v : grid)
	{
		for (int i = 0; i < grid.size(); ++i)
		{
			if (v[i] == 1)
			{
				++count;
			}
		}
		
	}

	std::cout << count;

	file.close();












	

	return 0;

}