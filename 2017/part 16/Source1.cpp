#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>


using namespace std;

struct StoredInstruction
{
	char type;

	int first = -1;
	int second = -1;

	int amount = -1;

};
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

constexpr int PART_2_COUNTER = 1000000000 ;
int main()
{
	fstream file; file.open("input.txt");
	string line;
	string programs = "abcdefghijklmnop";
	vector<StoredInstruction> instructions;


	while (getline(file, line, ','))
	{
		StoredInstruction currentInstruction;
		if (line[0] == 's')
		{
			int amount = 0;

			stringstream stream({ line.begin() + 1, line.end() });
			stream >> amount;

			currentInstruction.type = 's';
			currentInstruction.amount = amount;
			instructions.push_back(currentInstruction);
		}
		else if (line[0] == 'x')
		{
			int first = 0; int second = 0;

			line.replace(line.find('/'), 1, " ");
			stringstream stream({ line.begin() + 1, line.end() });
			stream >> first >> second;

			currentInstruction.type = 'x';
			currentInstruction.first = first;
			currentInstruction.second = second;
			instructions.push_back(currentInstruction);

		}
		else
		{
			char first = 0; char second = 0;
			line.replace(line.find('/'), 1, " ");
			stringstream stream({ line.begin() + 1, line.end() });

			stream >> first >> second;

			currentInstruction.type = 'p';
			currentInstruction.first = first;
			currentInstruction.second = second;
			instructions.push_back(currentInstruction);
		}


	}

	for (int i = 0; i < PART_2_COUNTER ; ++i)
	{
		for (const StoredInstruction& curr : instructions)
		{
			if (curr.type == 's')
			{
				Spin(programs, curr.amount);
			}
			else if (curr.type == 'x')
			{
				Exchange(programs, curr.first, curr.second);
			}
			else
			{
				Partner(programs, curr.first, curr.second);
			}


		}


		/* it always goes back to initial state after a certain amount of iterations */
		/* so get closest iteration to a billion and calculate from there */
		if (programs == "abcdefghijklmnop")
		{
			int backToInitial = i + 1;

			auto closest = PART_2_COUNTER % backToInitial ;


			i = backToInitial * ( PART_2_COUNTER / backToInitial);

			--i;




		}
	}

	cout << programs;
	return 0;
}