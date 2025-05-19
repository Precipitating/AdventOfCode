#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
using namespace std;

enum OP
{
	NOT_EQUAL,
	BIGGER_OR_EQUAL,
	BIGGER,
	EQUALS,
	LESS_OR_EQUAL,
	LESS

};


int main()
{
	fstream file; file.open("input.txt");
	string line;
	map<string, int> registers;
	int highestVal = 0;

	while (getline(file, line))
	{
		size_t fluffPos = line.find("if");

		line = line.erase(fluffPos, 3);

		string firstReg;
		string incOrDec;
		int numToAddDec;
		string conditionReg;
		string op;
		int conditionVal;

		stringstream stream(line);

		stream >> firstReg >> incOrDec >> numToAddDec >> conditionReg >> op >> conditionVal;

		OP currentOperator;
		if (op == "!=") { currentOperator = NOT_EQUAL; }
		else if (op == ">=") { currentOperator = BIGGER_OR_EQUAL; }
		else if (op == ">") { currentOperator = BIGGER; }
		else if (op == "==") { currentOperator = EQUALS; }
		else if (op == "<=") { currentOperator = LESS_OR_EQUAL; }
		else { currentOperator = LESS; }

		switch (currentOperator)
		{
		case NOT_EQUAL:
		{
			if (registers[conditionReg] != conditionVal)
			{
				if (incOrDec == "inc")
				{
					registers[firstReg] += numToAddDec;
				}
				else
				{
					registers[firstReg] -= numToAddDec;
				}
			}
			break;
		}
		case BIGGER_OR_EQUAL:
		{
			if (registers[conditionReg] >= conditionVal)
			{
				if (incOrDec == "inc")
				{
					registers[firstReg] += numToAddDec;
				}
				else
				{
					registers[firstReg] -= numToAddDec;
				}
			}
			break;
		}
		case BIGGER:
		{
			if (registers[conditionReg] > conditionVal)
			{
				if (incOrDec == "inc")
				{
					registers[firstReg] += numToAddDec;
				}
				else
				{
					registers[firstReg] -= numToAddDec;
				}
			}
			break;
		}
		case EQUALS:
		{
			if (registers[conditionReg] == conditionVal)
			{
				if (incOrDec == "inc")
				{
					registers[firstReg] += numToAddDec;
				}
				else
				{
					registers[firstReg] -= numToAddDec;
				}
			}
			break;
		}
		case LESS_OR_EQUAL:
		{
			if (registers[conditionReg] <= conditionVal)
			{
				if (incOrDec == "inc")
				{
					registers[firstReg] += numToAddDec;
				}
				else
				{
					registers[firstReg] -= numToAddDec;
				}
			}
			break;
		}
		case LESS:
		{
			if (registers[conditionReg] < conditionVal)
			{
				if (incOrDec == "inc")
				{
					registers[firstReg] += numToAddDec;
				}
				else
				{
					registers[firstReg] -= numToAddDec;
				}
			}
			break;
		}
		default:
			cout << "currentOperator has wrong assignment";
			break;


		}


		using pair_type = decltype(registers)::value_type;

		auto pr = std::max_element
		(
			std::begin(registers), std::end(registers),
			[](const pair_type& p1, const pair_type& p2) {
				return p1.second < p2.second;
			}
		);

		if (pr->second > highestVal)
		{
			highestVal = pr->second;
		}
	}
	cout << highestVal;
	return 0;
}