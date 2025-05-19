#include <iostream>
#include <vector>

using namespace std;



void ProcessPart2(int num,int row, int col, vector<vector<int>> &grid, bool& found)
{
	int count = 0;
	int result = 0;




	result += grid[row][col + 1];
	result += grid[row][col - 1];
	result += grid[row + 1][col];
	result += grid[row - 1][col];
	result += grid[row - 1][col+1];
	result += grid[row - 1][col-1];
	result += grid[row + 1][col+1];
	result += grid[row + 1][col-1];
	//result += num;

	grid[row][col] = result;

	if (result > 325489)
	{
		cout << result << '\n';
		found = true;
	}






}

int main()
{
	vector<vector<int>> grid(1000, std::vector<int>(1000, 0));
	int directionCnt[5] = { 1,1,2,2,2 };
	int directionCnt2[5] = { 1,1,2,2,2 };
	int input = 325489;
	int row = 500, col = 500;
	char move = 'r';
	int num = 2;
	grid[500][500] = 1;

	bool found = false;

	do
	{
		switch (move)
		{
		case 'r':
			col += 1;
			ProcessPart2(num, row, col, grid, found);
			move = 'u';
			--directionCnt2[0];
			++num;
			break;
		case 'u':
			if (directionCnt2[1] == 0)
			{
				directionCnt[1] += 2;
				move = 'l';
			}
			else
			{
				row -= 1;
				ProcessPart2(num, row, col, grid, found);
				--directionCnt2[1];
				++num;
			}
			break;
		case 'l':
			if (directionCnt2[2] == 0)
			{
				directionCnt[2] += 2;
				move = 'd';
			}
			else
			{
				col -= 1;
				ProcessPart2(num, row, col, grid, found);
				--directionCnt2[2];
				++num;
			}

			break;
		case 'd':
			if (directionCnt2[3] == 0)
			{
				directionCnt[3] += 2;
				move = 'x';
			}
			else
			{
				row += 1;
				ProcessPart2(num, row, col, grid, found);
				--directionCnt2[3];
				++num;
			}
			break;
		case 'x':

			col += 1;
			ProcessPart2(num, row, col, grid, found);
			--directionCnt2[4];
			++num;
			if (directionCnt2[4] == 0)
			{
				directionCnt[4] += 2;
				move = 'r';
			}
			break;

		}

		if (directionCnt2[0] == 0 && directionCnt2[1] == 0 && directionCnt2[2] == 0 && directionCnt2[3] == 0 && directionCnt2[4] == 0)
		{
			directionCnt2[0] = directionCnt[0];
			directionCnt2[1] = directionCnt[1];
			directionCnt2[2] = directionCnt[2];
			directionCnt2[3] = directionCnt[3];
			directionCnt2[4] = directionCnt[4];
		}


	} while (!found);

	found = false;








	return 0;
}