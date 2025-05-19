#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <regex>
#include <vector>
#include <set>
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
	vector<vector<short>> grid(1000, vector<short>(1000, 0));
	int overlapInch = 0;
	set<short> overlappedIds;
	int maxID = 0;

	Claim temp;
	while (getline(file, line))
	{
		line = regex_replace(line, fluffRemover, " ");
		stringstream stream(line);

		stream >> temp.id >> temp.leftOffset >> temp.topOffset >> temp.width >> temp.height;
		++maxID;

		for (int i = 0; i < temp.height; ++i)
		{
			for (int j = 0; j < temp.width; ++j)
			{
				if (grid[temp.topOffset + i][temp.leftOffset + j] != 0)
				{
					overlappedIds.insert(grid[temp.topOffset + i][temp.leftOffset + j]);
					overlappedIds.insert(temp.id);
				}
				else
				{
					grid[temp.topOffset + i][temp.leftOffset + j] = temp.id;
				}
			}
		}



	}



	for (int i = 1; i < maxID; ++i)
	{
		if (overlappedIds.count(i) == 0)
		{
			cout << i;
		}
	}





	return 0;
}