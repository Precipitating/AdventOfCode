#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

bool Exists(const string& line, const string& target)
{

	return line.find(target) != string::npos;
}

void Process(vector<string>& instructions, map<char, long long>& registers,  queue<long long>& ownQueue, queue<long long>& otherQueue, int id, int& currentIdx, int& sendVal)
{
	registers['p'] = id;
	for (int i = currentIdx; i < instructions.size(); ++i)
	{

		if (Exists(instructions[i], "snd"))
		{
			string input = { instructions[i].begin() + 4, instructions[i].end() };


			if (isdigit(input[0]))
			{
				otherQueue.push(input[0] - '0');
			}
			else
			{
				char reg = input[0];

				otherQueue.push(registers[reg]);

			}

			if (id == 1)
			{
				++sendVal;
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
		else if (Exists(instructions[i], "mod"))
		{
			string input = { instructions[i].begin() + 4, instructions[i].end() };

			char reg = input[0];
			input = input.substr(2);
			if (isalpha(input[0]))
			{
				char reg2 = input[0];

				registers[reg] %= registers[reg2];

			}
			else
			{
				long long dig = stoi(input);
				registers[reg] %= dig;
			}


		}
		else if (Exists(instructions[i], "rcv"))
		{
			string input = { instructions[i].begin() + 4, instructions[i].end() };
			char reg = input[0];


			if (ownQueue.size() != 0)
			{
				registers[reg] = ownQueue.front();
				ownQueue.pop();
			}
			else
			{
				currentIdx = i;
				return;
			}



		}
		else if (Exists(instructions[i], "jgz"))
		{
			string input = { instructions[i].begin() + 4, instructions[i].end() };

			if (isdigit(input[0]))
			{
				stringstream stream(input);
				long long dig;
				long long dig2;

				stream >> dig >> dig2;

				if (dig > 0)
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

						if (registers[reg] > 0)
						{
							i += dig;
							--i;
						}

					}
				}



			}
		}

	}

}
int main()
{
	fstream file; file.open("input.txt");
	string line;
	map<char, long long> registers;
	map<char, long long> registers2;

	vector<string> instructions;
	vector<string> instructions2;

	queue<long long> queue1;
	queue<long long> queue2;

	int currentIdx1 = 0;
	int currentIdx2 = 0;

	int sendVal = 0;

	while (getline(file, line))
	{
		instructions.push_back(line);


	}
	instructions2 = instructions;

	do
	{
		Process(instructions, registers, queue1, queue2, 0, currentIdx1, sendVal);
		Process(instructions2, registers2, queue2, queue1, 1, currentIdx2, sendVal);

	} while ( (currentIdx1 < instructions.size() - 1) || (currentIdx2 < instructions2.size() - 1));

	cout << sendVal;


	return 0;
}