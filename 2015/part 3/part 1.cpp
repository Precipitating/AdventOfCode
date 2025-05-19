#include <iostream>
#include <vector>
#include <array>
#include <sstream>
#include <fstream>


int main()
{
	std::fstream file;
	int currentColumn = 500;
	int currentRow = 500;


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
		switch (c)
		{
		case '<':
			currentColumn -= 1;
			multiArray[currentColumn][currentRow] += 1;
			break;
		case '>':
			currentColumn += 1;
			multiArray[currentColumn][currentRow] += 1;
			break;
		case '^':
			currentRow += 1;
			multiArray[currentColumn][currentRow] += 1;
			break;
		case 'v':
			currentRow -= 1;
			multiArray[currentColumn][currentRow] += 1;
			break;


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





	
	




	return 0;

}





