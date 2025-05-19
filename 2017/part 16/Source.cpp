#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void Spin(string& program, int amount)
{
	rotate(program.rbegin(), program.rbegin() + amount, program.rend());
}

void Exchange(string& program, size_t first, size_t second)
{
	swap(program[first], program[second]);
}

void Partner(string& program, char first, char second)
{
	auto firstPos = find(program.begin(), program.end(), first);
	auto secondPos = find(program.begin(), program.end(), second);
	iter_swap(firstPos, secondPos);
}

const int PART_2_COUNTER = 1000000000;
int main()
{
	fstream file; file.open("input.txt");
	string line;
	string programs = "abcdefghijklmnop";

	while (getline(file, line, ','))
	{
		if (line[0] == 's')
		{
			int amount = 0;
			stringstream stream({ line.begin() + 1, line.end() });
			stream >> amount;
			Spin(programs, amount);
		}
		else if (line[0] == 'x')
		{
			int first = 0; int second = 0;
			line.replace(line.find('/'), 1, " ");
 			stringstream stream({ line.begin() + 1, line.end() });

			stream >> first >> second;

			Exchange(programs, first, second);

		}
		else
		{
			char first = 0; char second = 0;
			line.replace(line.find('/'), 1, " ");
			stringstream stream({ line.begin() + 1, line.end() });

			stream >> first >> second;

			Partner(programs, first, second);
		}


	}


	cout << programs;
	return 0;
}