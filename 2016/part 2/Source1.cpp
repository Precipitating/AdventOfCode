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
	int grid[5][5] = { 0 };
	grid[0][0] = -1; grid[0][1] = -1; grid[0][2] = 1; grid[0][3] = -1; grid[0][4] = -1;
	grid[1][0] = -1; grid[1][1] = 2; grid[1][2] = 3; grid[1][3] = 4; grid[1][4] = -1;
	grid[2][0] = 5; grid[2][1] = 6; grid[2][2] = 7; grid[2][3] = 8; grid[2][4] = 9;
	grid[3][0] = -1; grid[3][1] = 4; grid[3][2] = 8; grid[3][3] = 3; grid[3][4] = -1;
	grid[4][0] = -1; grid[4][1] = -1; grid[4][2] = 7; grid[4][3] = -1; grid[4][4] = -1;

	int posRow = 2;
	int posColumn = 0;
	/* A = 4, B = 8, C = 3 */
	/* D = 7*/
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
				if ((posRow - 1) > -1 && (grid[posRow-1][posColumn]) != -1)
				{
					posRow -= 1;
				}
				break;
			}
			case 'D':
			{
				if ((posRow + 1) < 5 && (grid[posRow + 1][posColumn]) != -1)
				{
					posRow += 1;
				}
				break;
			}
			case 'L':
				if ((posColumn - 1) > -1 && (grid[posRow ][posColumn - 1]) != -1)
				{
					posColumn -= 1;
				}
				break;

			case 'R':
				if ((posColumn + 1) < 5 && (grid[posRow][posColumn + 1]) != -1)
				{
					posColumn += 1;
				}
				break;

			}
		}


		if (posRow == 3 && posColumn == 1)
		{
			finalCode.append("A");
		}
		else if (posRow == 3 && posColumn == 2)
		{
			finalCode.append("B");
		}
		else if (posRow == 3 && posColumn == 3)
		{
			finalCode.append("C");
		}
		else if (posRow == 4 && posColumn == 2)
		{
			finalCode.append("D");
		}
		else
		{
			finalCode.append(to_string(grid[posRow][posColumn]));
		}

	}

	return 0;
}
