#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>
#include <vector>
#include <cmath>


using namespace std;


enum Direction
{
	NORTH,
	EAST,
	SOUTH,
	WEST
};

int main()
{
	vector<vector<int>> coord(500, vector<int>(500,0));
	regex removeComma(",");
	fstream file; file.open("input.txt");
	string line;
	Direction dir = NORTH;
	int y = 250; int x = 250;

	while (getline(file, line))
	{
		char direction;
		int steps;
		line = regex_replace(line, removeComma, "");
		stringstream stream(line);

		while (stream >> direction >> steps)
		{
			switch (direction)
			{
			case 'R':
			{
				if (dir == WEST)
				{
					dir = NORTH;
				}
				else
				{
					dir = static_cast<Direction>(static_cast<Direction>(dir + 1));
				}
			}
				break;
			case 'L':
				if (dir == NORTH)
				{
					dir = WEST;
				}
				else
				{
					dir = static_cast<Direction>(static_cast<Direction>(dir - 1));
				}
				break;

			}

			switch (dir)
			{
			case NORTH: y += steps; break;
			case EAST:	x += steps;	break;
			case SOUTH:	y -= steps;	break;
			case WEST:	x -= steps;	break;
			default:	cout << "fail";
			}




		}
		

		coord[y][x] = 1;

		int destinationY = y; int destinationX = x;

		int blocks = abs(150 - destinationY) + abs(150 - destinationX);

		/* destination found and block figured out*/








	}



	return 0;
}