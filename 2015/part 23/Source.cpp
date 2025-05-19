#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

struct Register
{
	string instruction, reg;
	int value = 0;

};

int main()
{
	regex removeComma(",");
	regex jmpCheck("jmp");
	vector<Register> list;
	fstream file;
	file.open("input.txt");
	string line;


	while (getline(file, line))
	{
		Register tempReg;
		stringstream stream(line);

		if (regex_search(line, removeComma))
		{
			line = regex_replace(line, removeComma, "");
			stream >> tempReg.instruction >> tempReg.reg >> tempReg.value;
		}
		else if (regex_search(line, jmpCheck))
		{
			stream >> tempReg.instruction >> tempReg.value;
		}
		else
		{
			stream >> tempReg.instruction >> tempReg.reg;
		}

		list.push_back(tempReg);


	}


	unsigned int a = 1;
	unsigned int b = 0;

	for (int i = 0; i < list.size(); ++i)
	{
		string& instruction = list[i].instruction;
		if (instruction == "hlf")
		{
			if (list[i].reg == "a")
			{
				a /= 2;

			}
			else
			{
				b /= 2;
			}
		}
		else if (instruction == "tpl")
		{
			if (list[i].reg == "a")
			{
				a *= 3;

			}
			else
			{
				b *= 3;
			}
		}
		else if (instruction == "inc")
		{
			if (list[i].reg == "a")
			{
				++a;

			}
			else
			{
				++b;
			}
		}
		else if (instruction == "jmp")
		{
			i += list[i].value - 1;
		}
		else if (instruction == "jie")
		{
			if (list[i].reg == "a,")
			{
				if (a % 2 == 0)
				{
					i += list[i].value - 1;
				}

			}
			else
			{
				if (b % 2 == 0)
				{
					i += list[i].value - 1;
				}
			}
		}
		else if (instruction == "jio")
		{
			if (list[i].reg == "a,")
			{
				if (a == 1)
				{
					i += list[i].value - 1;
				}

			}
			else
			{
				if (b == 1 )
				{
					i += list[i].value - 1;
				}
			}
		}





	}


	cout << b;
	return 0;
}