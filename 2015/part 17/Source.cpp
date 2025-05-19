#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include "Header.h"

using namespace std;



int main()
{
	fstream file;
	file.open("input.txt");
	vector<int> containerSizes;
	string line;
	int combos = 0;



	while (getline(file, line))
	{
		int number;
		stringstream stream(line);

		stream >> number;
		containerSizes.push_back(number);

	}


	typedef vector<int>::iterator Iter;


	for (int i = 3; i < containerSizes.size(); ++i)
	{
		for_each_combination(containerSizes.begin(), containerSizes.begin() + i, containerSizes.end(),
			[&combos](Iter f, Iter l)
			{
				int result = 0;
				for (; f != l; ++f)
					result += *f;
				//std::cout << "| ";

				if (result == 150)
				{
					++combos;
				}
			//	std::cout << "\n";
				return false;
			}
		);
	}


	std::cout << combos;




	return 0;
}