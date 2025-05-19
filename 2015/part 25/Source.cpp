#include <iostream>
#include <vector>

using namespace std;
int main()
{
	vector<vector<unsigned long long>> container(10000, vector<unsigned long long>(10000,0));
	container[0][0] = 20151125;

	int nextRow = 1;
	int currentRow = 1;
	int currentColumn = 0;

	unsigned long long previousNumber = container[0][0];
	do
	{

		if ( currentColumn <= container.size() && (currentRow > -1 && currentRow <= container.size() -1))
		{
			unsigned long long multiply = previousNumber * 252533;
			container[currentRow][currentColumn] = multiply % 33554393;
			previousNumber = container[currentRow][currentColumn];

			++currentColumn;

			--currentRow;

		}
		else
		{
			currentColumn = 0;

			if ((nextRow + 1) < container.size())
			{
				currentRow = nextRow + 1;
				++nextRow;
			}
			else if (currentRow < 0)
			{
				currentRow = nextRow + 1;
				++nextRow;
			}
				
		}

	} while (container[3010][3019] <= 0);

	return 0;
}