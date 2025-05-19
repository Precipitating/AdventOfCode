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
	regex tglFilter("tgl");
	vector<string> instructions;

	map<char, int> registers;
	registers.insert(make_pair('a', 12));
	registers.insert(make_pair('b', 0));
	registers.insert(make_pair('c', 0));
	registers.insert(make_pair('d', 0));

	int a = 0, b = 0, c = 0, d = 0;

	while (getline(file, line))
	{
		instructions.push_back(line);
	}
	file.clear();
	file.seekg(0);


	for (int i = 0; i < instructions.size(); ++i)
	{
		string currentInstruction = instructions[i];


		/* part 2 optimisations*/
		/* line 10 in input basically does a += (c * d) so we just do it in 1 operation if we reach this instruction */
		if (i == 9)
		{
			registers['c'] = registers['b'];
			registers['a'] += (registers['c'] * registers['d']);
			registers['c'] = 0;
			registers['d'] = 0;
			continue;


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

			++registers[regToInc];


		}
		else if (regex_search(currentInstruction, decFilter))
		{
			currentInstruction = regex_replace(currentInstruction, decFilter, "");
			EraseWhitespace(currentInstruction);
			char regToDec = currentInstruction[0];

			--registers[regToDec];


		}
		else if (regex_search(currentInstruction, tglFilter))
		{
			currentInstruction = regex_replace(currentInstruction, tglFilter, "");
			EraseWhitespace(currentInstruction);
			char reg = currentInstruction[0];

			int targetInstruction = i + registers[reg];

			if (targetInstruction < instructions.size() && targetInstruction > -1)
			{
				/* start modifying single instructions */
				if (regex_search(instructions[targetInstruction], incFilter))
				{
					instructions[targetInstruction] = regex_replace(instructions[targetInstruction], incFilter, "dec");
				}
				else if (regex_search(instructions[targetInstruction], decFilter) || regex_search(instructions[targetInstruction], tglFilter))
				{
					instructions[targetInstruction] = regex_replace(instructions[targetInstruction], tglFilter, "inc");
				}
				/* now modify double */
				else if (regex_search(instructions[targetInstruction], jmpFilter))
				{
					instructions[targetInstruction] = regex_replace(instructions[targetInstruction], jmpFilter, "cpy");
				}
				else if (regex_search(instructions[targetInstruction], cpyFilter))
				{
					instructions[targetInstruction] = regex_replace(instructions[targetInstruction], cpyFilter, "jnz");
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
					if (isdigit(currentInstruction[0]))
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


	cout << registers['a'];


	return 0;
}