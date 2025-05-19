#include <iostream>
#include <vector>
#include <array>
#include <sstream>
#include <fstream>

enum SANTA_TYPE
{
	SANTA = 0,
	ROBOT_SANTA = 1
	
};
int main()
{
	std::fstream file;
	int currentColumn = 500;
	int currentRow = 500;

	int currentColumnR = 500;
	int currentRowR = 500;
	SANTA_TYPE currentSanta = (SANTA_TYPE)0;

	int twoPresentHouses = 0;
	/* vector is the row, array is the column*/
	std::vector<std::array<int, 1000>> multiArray(1000);

	/* lets put starting position in middle of 2D array so we dont go out of bounds somehow */
	multiArray[500][500] = 1;

	char c;
	file.open("input.txt", std::ios::in);

	/* read char by char*/
	while (file.get(c))
	{
		if (currentSanta == SANTA)
		{
			switch (c)
			{
			case '<':
				currentColumn -= 1;
				multiArray[currentRow][currentColumn] += 1;
				break;
			case '>':
				currentColumn += 1;
				multiArray[currentRow][currentColumn] += 1;
				break;
			case '^':
				currentRow += 1;
				multiArray[currentRow][currentColumn] += 1;
				break;
			case 'v':
				currentRow -= 1;
				multiArray[currentRow][currentColumn] += 1;
				break;
			}

			currentSanta = (SANTA_TYPE)!currentSanta;
		}
		else if (currentSanta == ROBOT_SANTA)
		{
			switch (c)
			{
			case '<':
				currentColumnR -= 1;
				multiArray[currentRowR][currentColumnR] += 1;
				break;
			case '>':
				currentColumnR += 1;
				multiArray[currentRowR][currentColumnR] += 1;
				break;
			case '^':
				currentRowR += 1;
				multiArray[currentRowR][currentColumnR] += 1;
				break;
			case 'v':
				currentRowR -= 1;
				multiArray[currentRowR][currentColumnR] += 1;
				break;
			}
			currentSanta = (SANTA_TYPE)!currentSanta;
		}
		
	}


	// if any element in the 2d array is above or equal 1, then we know santa has already delivered there.
	for (int row = 0; row < 1000; ++row)
	{
		for (int column = 0; column < 1000; ++column)
		{
			if (multiArray[row][column] >= 1)
			{
				++twoPresentHouses;
			}
		}

	}







	std::cout << "Houses that santa has already delivered to:  " << twoPresentHouses;



	return 0;

}





