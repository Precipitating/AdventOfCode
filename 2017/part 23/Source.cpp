#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

bool Exists(const string& line, const string& target)
{

	return line.find(target) != string::npos;
}
int main()
{
	fstream file; file.open("input.txt");
	string line;
	map<char, long long> registers;
	vector<long long> lastSound;
	vector<string> instructions;

	int part1cnt = 0;


	while (getline(file, line))
	{
		instructions.push_back(line);


	}


	for (int i = 0; i < instructions.size(); ++i)
	{

		if (Exists(instructions[i], "sub"))
		{
			string input = { instructions[i].begin() + 4, instructions[i].end() };
			char reg = input[0];
			input = input.substr(2);

			if (any_of(input.begin(), input.end(), ::isdigit))
			{
				long long dig = stoi(input);

				registers[reg] -= dig;

			}
			else
			{
				char reg2 = input[0];

				registers[reg] -= registers[reg2];
			}


		}
		else if (Exists(instructions[i], "set"))
		{
			string input = { instructions[i].begin() + 4, instructions[i].end() };

			char reg = input[0];
			input = input.substr(2);
			if (isalpha(input[0]))
			{
				char reg2 = input[0];
				registers[reg] = registers[reg2];
			}
			else
			{
				long long val = stoi(input);

				registers[reg] = val;
			}
		}
		else if (Exists(instructions[i], "add"))
		{
			string input = { instructions[i].begin() + 4, instructions[i].end() };
			char reg = input[0];
			input = input.substr(2);

			if (any_of(input.begin(), input.end(), ::isdigit))
			{
				long long dig = stoi(input);

				registers[reg] += dig;

			}
			else
			{
				char reg2 = input[0];

				registers[reg] += registers[reg2];
			}



		}
		else if (Exists(instructions[i], "mul"))
		{
			++part1cnt;
			string input = { instructions[i].begin() + 4, instructions[i].end() };
			char reg = input[0];
			input = input.substr(2);

			if (isalpha(input[0]))
			{
				char reg2 = input[0];

				registers[reg] *= registers[reg2];
			}
			else
			{
				long long dig = stoi(input);

				registers[reg] *= dig;
			}


		}
		else if (Exists(instructions[i], "jnz"))
		{
			string input = { instructions[i].begin() + 4, instructions[i].end() };

			if (isdigit(input[0]))
			{
				stringstream stream(input);
				long long dig;
				long long dig2;

				stream >> dig >> dig2;

				if (dig != 0)
				{
					i += dig2;
					--i;
				}
			}
			else
			{
				if (isalpha(input[0]))
				{
					char reg = input[0];

					if (isalpha(input[2]))
					{
						char reg2 = input[2];

						if (registers[reg] > 0)
						{
							i += registers[reg2];
							--i;
						}

					}
					else
					{
						long long dig;
						input = { input.begin() + 2, input.end() };
						stringstream stream(input);

						stream >> dig;

						if (registers[reg] != 0)
						{
							i += dig;
							--i;
						}

					}
				}



			}
		}



	}
	cout << part1cnt;

	return 0;
}