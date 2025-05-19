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
	vector<vector<int>> coord(500, vector<int>(500, 0));
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
			case NORTH:
			{
				int finalResult = y + steps;
				do
				{
					coord[x][y + 1] += 1;
					if (coord[x][y + 1] == 2)
					{
						int realResult = std::abs(150 - (y + 1)) + std::abs(150 - x);
					}
					++y;

				} while (y != finalResult);

				break;
			}
			case EAST:
			{
				int finalResult = x + steps;
				do
				{
					coord[x + 1][y] += 1;
					if (coord[x + 1][y] == 2)
					{
						int realResult = std::abs(150 - y) + std::abs(150 - (x + 1));
					}
					++x;

				} while (x != finalResult);
				break;

			}
			case SOUTH:
			{

				int finalResult = y - steps;
				do
				{
					coord[x][y - 1] += 1;
					if (coord[x][y-1] == 2)
					{
						int realResult = std::abs(150 - (y - 1)) + std::abs(150 - x);
					}
					--y;

				} while (y != finalResult);
				break;

			}
			case WEST:
			{

				int finalResult = x - steps;
				do
				{
					coord[x - 1][y] += 1;
					if (coord[x - 1][y] == 2)
					{
						int realResult = std::abs(150 - y) + std::abs(150 - (x - 1));
					}
					--x;

				} while (x != finalResult);
				break;

			}
			default:	cout << "fail";
			}

			//if (coord[y][x] == 2)
			//{
			//	int blocks1 = std::abs(150 - y) + std::abs(150 - x);
			//}
			//else
			//{
			//	coord[y][x] += 1;
			//}




		}


		coord[y][x] = 1;

		int destinationY = y; int destinationX = x;
		int blocks = abs(250 - 131) + abs(250 - 236);

		/* destination found and block figured out*/








	}



	return 0;
}