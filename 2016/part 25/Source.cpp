#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include <map>


using namespace std;


void EraseWhitespace(string& input)
{
	while (input[0] == ' ')
	{
		input = input.erase(0, 1);
	}
}
int main()
{
	fstream file; file.open("input.txt");
	string line;
	regex cpyFilter("cpy");
	regex incFilter("inc");
	regex decFilter("dec");
	regex jmpFilter("jnz");
	regex tglFilter("out");
	vector<string> instructions;
	string clockChecker;
	regex clockSignalCheck("^(01)+$");

	map<char, int> registers;
	registers.insert(make_pair('a', 6));
	registers.insert(make_pair('b', 0));
	registers.insert(make_pair('c', 0));
	registers.insert(make_pair('d', 0));

	int a = 0, b = 0, c = 0, d = 0;

	int cntr = 0;

	while (getline(file, line))
	{
		instructions.push_back(line);
	}
	file.clear();
	file.seekg(0);


	for (int i = 0; i < instructions.size(); ++i)
	{
		string currentInstruction = instructions[i];

		//if (i == 3)
		//{
		//	registers['d'] += registers['b'] * registers['c'];
		//	registers['b'] = 0; registers['c'] = 0;
		//	i += 4;
		//	continue;
		//}


		if (i == 13)
		{
			//registers['a'] = registers['b'] / 2;
			//registers['b'] = 0;
			//registers['c'] = 2;
			//continue;

		}


		/* if instruction is copy do it */
		if (regex_search(currentInstruction, cpyFilter))
		{
			currentInstruction = regex_replace(currentInstruction, cpyFilter, "");
			EraseWhitespace(currentInstruction);
			stringstream stream(currentInstruction);

			if (!isdigit(currentInstruction[0]) && currentInstruction[0] != '-')
			{
				char reg = currentInstruction[0];
				currentInstruction = currentInstruction.erase(0, 1);
				EraseWhitespace(currentInstruction);
				char regTo = currentInstruction[0];

				registers[regTo] = registers[reg];

			}
			else
			{
				currentInstruction = regex_replace(currentInstruction, cpyFilter, "");
				EraseWhitespace(currentInstruction);
				stringstream stream(currentInstruction);

				int numberToCpy = 0;
				stream >> numberToCpy;

				string numberToStr = to_string(numberToCpy);
				EraseWhitespace(currentInstruction);
				currentInstruction = currentInstruction.erase(0, numberToStr.length());
				EraseWhitespace(currentInstruction);

				if (isdigit(currentInstruction[0]))
				{
					continue;
				}
				char registerTo = currentInstruction[0];

				registers[registerTo] = numberToCpy;




			}
		}
		else if (regex_search(currentInstruction, incFilter))
		{
			currentInstruction = regex_replace(currentInstruction, incFilter, "");
			EraseWhitespace(currentInstruction);
			char regToInc = currentInstruction[0];

			registers[regToInc] += 1;


		}
		else if (regex_search(currentInstruction, decFilter))
		{
			currentInstruction = regex_replace(currentInstruction, decFilter, "");
			EraseWhitespace(currentInstruction);
			char regToDec = currentInstruction[0];

			registers[regToDec] -= 1;


		}
		else if (regex_search(currentInstruction, tglFilter))
		{
			currentInstruction = regex_replace(currentInstruction, tglFilter, "");
			EraseWhitespace(currentInstruction);
			char reg = currentInstruction[0];

			

			if (clockChecker.size() < 10)
			{
				int val = registers[reg];
				clockChecker.append(to_string(val));
			}
			else
			{
				if (regex_match(clockChecker,clockSignalCheck))
				{
					cout << cntr << '\n';
					break;
				}
				else
				{

					clockChecker.clear();
					++cntr;
					registers['a'] = cntr;
					registers['d'] = 0;
					registers['c'] = 0;
					registers['b'] = 0;
					i = -1;

				}
			}

		


		}
		else
		{
			currentInstruction = regex_replace(currentInstruction, jmpFilter, "");
			EraseWhitespace(currentInstruction);
			char regToCheck = currentInstruction[0];

			if (!isdigit(regToCheck))
			{
				if (registers[regToCheck] != 0)
				{
					currentInstruction = currentInstruction.erase(0, 1);
					EraseWhitespace(currentInstruction);
					stringstream stream(currentInstruction);
					int offset = 0;
					stream >> offset;

					int finalOffset = i + offset;
					/* counteract the for loop from incrementing i so it doesnt skip the jumped instruction */
					if (finalOffset > instructions.size() - 1)
					{
						i = instructions.size();
					}
					else
					{
						i += offset;
						--i;
					}






				}
			}
			else
			{
				int dig = regToCheck - '0';

				if (dig != 0)
				{
					currentInstruction = currentInstruction.erase(0, 1);
					EraseWhitespace(currentInstruction);
					stringstream stream(currentInstruction);
					int offset = 0;
					if (isdigit(currentInstruction[0]) || currentInstruction[0] == '-')
					{
						offset = 0;
						stream >> offset;
					}
					else
					{
						offset = registers[currentInstruction[0]];
					}


					int finalOffset = i + offset;
					/* counteract the for loop from incrementing i so it doesnt skip the jumped instruction */
					if (finalOffset > instructions.size() - 1)
					{
						i = instructions.size();
					}
					else
					{
						i += offset;
						--i;
					}



				}
			}




		}


	}





	return 0;
}