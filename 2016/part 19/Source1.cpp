#include <iostream>
#include <vector>
#include <list>

const int INPUT = 3004953;
const int INPUT2 = 10;

int main()
{
	int j = 1;

	while (j * 3 < INPUT)
	{
		j *= 3;

		if (INPUT - j <= j)
		{
			std::cout << INPUT - j << '\n';
		}
		else
		{
			std::cout << j + (INPUT - j * 2) * 2 << '\n';
		}
	}


	return 0;
}