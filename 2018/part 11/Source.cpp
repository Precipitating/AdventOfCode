#include <iostream>
#include <vector>
using namespace std;


int GetRackId(int x)
{
	return x + 10;

}

int Get3x3(const vector<vector<int>>& grid, int startRow, int startCol, int gridSize)
{
	int result = 0;
	for (size_t i = 0; i < gridSize; ++i)
	{
		for (size_t j = 0; j < gridSize; ++j)
		{
			result += grid[startRow + i][startCol + j];
		}
	}

	return result;

}



int CalculatePower(int x, int y, int serialNum)
{
	int rackId = GetRackId(x);
	// begin power level
	int powerLevel = rackId * y;

	// increase power level
	powerLevel += serialNum;
	powerLevel *= rackId;
	powerLevel = (powerLevel / 100) % 10;
	powerLevel -= 5;

	return powerLevel;



}

vector<vector<int>> BuildSAT(const vector<vector<int>>& grid)
{
	// build summed area table
	int n = grid.size();
	vector<vector<int>> sat(n, vector<int>(n));

	for (size_t y = 1; y < n; ++y)
	{
		for (size_t x = 1; x < n; ++x)
		{
			sat[y][x] = grid[y][x] + sat[y - 1][x] + sat[y][x - 1] - sat[y - 1][x - 1];

		}

	}
	return sat;
}


int GetRegionSum(const vector<vector<int>>& sat, int x, int y, int size)
{
	int x2 = x + size - 1;
	int y2 = y + size - 1;

	int total = sat[y2][x2] - sat[y - 1][x2]- sat[y2][x - 1] + sat[y - 1][x - 1];

	return total;
}

int main()
{
	int input = 7989;
	//int input = 18;
	vector<vector<int>> grid(301, vector<int>(301));

	// populate grid
	for (size_t i = 1; i < 300; ++i)
	{
		for (size_t j = 1; j < 300; ++j)
		{
			grid[i][j] = CalculatePower(i, j, input);

		}
	}

	// find 3x3 best power
	int maxPower = INT_MIN;
	int maxSize = INT_MIN;
	pair<int, int> maxCoord = {};


	//for (size_t i = 1; i < 300; ++i)
	//{
	//	for (size_t j = 1; j < 300; ++j)
	//	{
	//		if (i + 3 > 300 || j + 3 > 300) continue;

	//		int power = Get3x3(grid, i, j, 3);
	//		if (power > maxPower)
	//		{
	//			maxPower = power;
	//			maxCoord = { i,j };
	//		}



	//	}
	//}


	// part 2
	vector<vector<int>> satGrid = BuildSAT(grid);

	for (int gridSize = 1; gridSize <= 300; ++gridSize)
	{
		for (int i = 1; i <= 300 - gridSize + 1; ++i)
		{
			for (int j = 1; j <= 300 - gridSize + 1; ++j)
			{
				int power = GetRegionSum(satGrid, i, j, gridSize);
				if (power > maxPower)
				{
					maxPower = power;
					maxCoord = { i, j };
					maxSize = gridSize;
				}
			}
		}
	}


	//cout << maxCoord.first << ',' <<  maxCoord.second;

	cout << maxCoord.second << ',' <<  maxCoord.first << ',' << maxSize;
	return 0;
}