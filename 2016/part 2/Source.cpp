#include <iostream>
#include <sstream>
#include <fstream>
#include <string>


using namespace std;

int main()
{
	fstream file; file.open("input.txt");
	string finalCode;
	string line;
	int grid[3][3] = { 0 };
	grid[0][0] = 1; grid[0][1] = 2; grid[0][2] = 3;
	grid[1][0] = 4; grid[1][1] = 5; grid[1][2] = 6;
	grid[2][0] = 7; grid[2][1] = 8; grid[2][2] = 9;

	int posRow = 1;
	int posColumn = 1;

	while (getline(file, line))
	{
		char currentButton;
		stringstream stream(line);


		while (stream >> currentButton)
		{
			switch (currentButton)
			{
			case 'U':
			{
				if ((posRow - 1) > -1)
				{
					posRow -= 1;
				}
				break;
			}
			case 'D':
			{
				if ((posRow + 1) < 3)
				{
					posRow += 1;
				}
				break;
			}
			case 'L':
				if ((posColumn - 1) > -1)
				{
					posColumn-= 1;
				}
				break;

			case 'R':
				if ((posColumn + 1) < 3)
				{
					posColumn += 1;
				}
				break;

			}
		}

		finalCode.append(to_string(grid[posRow][posColumn]));

	}

	return 0;
}
