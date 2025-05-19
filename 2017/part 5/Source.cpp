#include <iostream>
#include <fstream>
#include <vector>
#include <string>


using namespace std;

int main()
{
	fstream file; file.open("input.txt");
	vector<int> instructions;
	string line;
	int steps = 0;


	while (getline(file, line))
	{
		instructions.push_back(stoi(line));


	}

	for (size_t i = 0; i < instructions.size(); ++i)
	{
		int jumpVal = instructions[i];
		++instructions[i];

		i += (jumpVal - 1);

		if (i < instructions.size())
		{
			++steps;
		}

	}

	cout << steps;

	return 0;
}