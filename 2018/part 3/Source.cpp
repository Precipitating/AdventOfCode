#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <regex>
#include <vector>
using namespace std;

struct Claim
{
	short id;
	short leftOffset;
	short topOffset;
	short width;
	short height;



};

int main()
{
	fstream file; file.open("input.txt");
	string line;
	regex fluffRemover("#|@|,|:|x");
	vector<vector<short>> grid( 1000, vector<short>(1000,0));
	int overlapInch = 0;


	Claim temp;
	while (getline(file, line))
	{
		line = regex_replace(line, fluffRemover, " ");
		stringstream stream(line);

		stream >> temp.id >> temp.leftOffset >> temp.topOffset >> temp.width >> temp.height;

		for (int i = 0; i < temp.height; ++i)
		{
			for (int j = 0; j < temp.width; ++j)
			{
				if (grid[temp.topOffset + i][temp.leftOffset + j] != 0)
				{
					++grid[temp.topOffset + i][temp.leftOffset + j];
				}
				else
				{
					grid[temp.topOffset + i][temp.leftOffset + j] = 1;
				}
			}
		}



	}

	for (size_t i = 0; i < grid.size(); ++i)
	{
		for (size_t j = 0; j < grid.size(); ++j)
		{
			if (grid[i][j] > 1)
			{
				++overlapInch;
			}
		}
	}



	cout << overlapInch;





	return 0;
}