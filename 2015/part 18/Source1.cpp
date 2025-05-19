#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <array>
#include <algorithm>

using namespace std;

int CalculateDiagonals(const std::array<std::array<int, 100>, 100>& grid, int row, int column)
{
	int neighbours = 0;
	int currentChar = 1;
	int currentRow = row;
	int currentColumn = column;


	bool done = false;
	bool done2 = false;
	bool done3 = false;
	bool done4 = false;

	/* calculate forward diagonal neighbours*/

	if (currentRow < grid.size() - 1 && currentColumn < grid.size() - 1)
	{
		++currentRow;
		++currentColumn;


		if (grid[currentRow][currentColumn] == currentChar)
		{
			++neighbours;
		}
		else
		{
			done = true;
		}
	}
	else
	{
		done = true;
	}


	currentRow = row;
	currentColumn = column;

	/* calculate forward backward diagonal neighbours*/

	if (currentRow > 0 && currentColumn > 0)
	{
		--currentRow;
		--currentColumn;


		if (grid[currentRow][currentColumn] == currentChar)
		{
			++neighbours;
		}
		else
		{
			done2 = true;
		}
	}
	else
	{
		done2 = true;
	}


	currentRow = row;
	currentColumn = column;
	/* calculate backward diagonal neighbours*/

	if (currentRow < grid.size() - 1 && currentColumn > 0)
	{
		++currentRow;
		--currentColumn;


		if (grid[currentRow][currentColumn] == currentChar)
		{
			++neighbours;
		}
		else
		{
			done3 = true;
		}
	}
	else
	{
		done3 = true;
	}


	currentRow = row;
	currentColumn = column;

	/* calculate backward backward neighbours*/

	if (currentRow > 0 && currentColumn < grid.size() - 1)
	{
		--currentRow;
		++currentColumn;


		if (grid[currentRow][currentColumn] == currentChar)
		{
			++neighbours;
		}
		else
		{
			done4 = true;
		}
	}
	else
	{
		done4 = true;
	}




	return neighbours;

}



int CalculateForwardsBackwards(const std::array<std::array<int, 100>, 100>& grid, int row, int column)
{
	int neighbours = 0;
	int currentChar = 1;
	int currentRow = row;
	int currentColumn = column;


	bool done = false;
	bool done2 = false;



	/* calculate fowards*/

	if (currentColumn < grid.size() - 1)
	{
		++currentColumn;

		if (grid[currentRow][currentColumn] == currentChar)
		{
			++neighbours;
		}
		else
		{
			done = true;
		}
	}
	else
	{
		done = true;
	}


	currentRow = row;
	currentColumn = column;

	if (currentColumn > 0)
	{
		--currentColumn;

		if (grid[currentRow][currentColumn] == currentChar)
		{
			++neighbours;
		}
		else
		{
			done2 = true;
		}
	}
	else
	{
		done2 = true;
	}




	return neighbours;

}


int CalculateUpDown(const std::array<std::array<int, 100>, 100>& grid, int row, int column)
{
	int neighbours = 0;
	int currentChar = 1;
	int currentRow = row;
	int currentColumn = column;


	bool done = false;
	bool done2 = false;



	/* calculate up*/
	if (currentRow > 0)
	{
		--currentRow;

		if (grid[currentRow][currentColumn] == currentChar)
		{
			++neighbours;
		}
		else
		{
			done = true;
		}
	}
	else
	{
		done = true;
	}



	currentRow = row;
	currentColumn = column;

	/* calculate down*/

	if (currentRow < grid.size() - 1)
	{
		++currentRow;

		if (grid[currentRow][currentColumn] == currentChar)
		{
			++neighbours;
		}
		else
		{
			done2 = true;
		}
	}
	else
	{
		done2 = true;
	}



	return neighbours;

}



void NextStep(std::array<std::array<int, 100>, 100>& grid, int& currentStep)
{
	int on = 1;
	int off = 0;


	std::array<std::array<int, 100>, 100> tempGrid = grid;

	for (int i = 0; i < grid.size(); ++i)
	{
		for (int j = 0; j < grid.size(); ++j)
		{
			int neighbours = 0;
			/* calculate diagonals*/

			neighbours += CalculateDiagonals(grid, i, j);

			/* calculate forward/backwards*/

			neighbours += CalculateForwardsBackwards(grid, i, j);


			/* calculate up/down  */
			neighbours += CalculateUpDown(grid, i, j);



			if (grid[i][j] == on)
			{
				if (neighbours != 2 && neighbours != 3)
				{
					tempGrid[i][j] = 0;
				}
			}
			else if (grid[i][j] == off)
			{
				if (neighbours == 3)
				{
					tempGrid[i][j] = 1;
				}
			}
		}
	}

	grid = tempGrid;
	++currentStep;
}


int main()
{
	fstream file;
	file.open("input.txt");
	string line;
	std::array<std::array<int, 100>, 100> grid = {  };

	int nextRow = 0;

	/* set initial grid state */
	while (getline(file, line))
	{
		int nextColumn = 0;
		for (const char& light : line)
		{

			if (light == '#')
			{
				grid[nextRow][nextColumn] = 1;
			}


			++nextColumn;


		}

		++nextRow;

	}

	grid[0][0] = 1;
	grid[99][0] = 1;
	grid[0][99] = 1;
	grid[99][99] = 1;




	int currentStep = 0;

	/* animate grid per step */
	while (currentStep < 100)
	{
		NextStep(grid, currentStep);
		grid[0][0] = 1;
		grid[99][0] = 1;
		grid[0][99] = 1;
		grid[99][99] = 1;
	}


	int count = 0;
	for (int i = 0; i < grid.size(); ++i)
	{
		for (int j = 0; j < grid.size(); ++j)
		{
			if (grid[i][j] == 1)
			{
				++count;
			}
		}

	}

	cout << count;


	return 0;
}