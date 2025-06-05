#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_set>
#include "operations.h"

void Execute(vector<int>& reg, const string& op, int A, int B, int C)
{
	if (op == "addr") addr(reg, A, B, C);
	else if (op == "addi") addi(reg, A, B, C);
	else if (op == "mulr") mulr(reg, A, B, C);
	else if (op == "muli") muli(reg, A, B, C);
	else if (op == "banr") banr(reg, A, B, C);
	else if (op == "bani") bani(reg, A, B, C);
	else if (op == "borr") borr(reg, A, B, C);
	else if (op == "bori") bori(reg, A, B, C);
	else if (op == "setr") setr(reg, A, B, C);
	else if (op == "seti") seti(reg, A, B, C);
	else if (op == "gtir") gtir(reg, A, B, C);
	else if (op == "gtri") gtri(reg, A, B, C);
	else if (op == "gtrr") gtrr(reg, A, B, C);
	else if (op == "eqir") eqir(reg, A, B, C);
	else if (op == "eqri") eqri(reg, A, B, C);
	else if (op == "eqrr") eqrr(reg, A, B, C);


}

int main()
{
	fstream file("input.txt");
	string line;
	int boundRegister = 0;
	vector<int> registers(6, 0);
	vector<tuple<string, int, int, int>> instructions;
	vector<int> eqrrHitVals;
	unordered_set<int> seenValues;

	while (getline(file, line))
	{
		if (line.find('#') != string::npos)
		{
			boundRegister = line[4] - '0';

		}
		else
		{
			int A, B, C;
			string op;
			stringstream stream(line);
			stream >> op >> A >> B >> C;
			instructions.emplace_back(op, A, B, C);

		}
	}

	int ip = 0;
	while (ip >= 0 && ip < instructions.size())
	{
		registers[boundRegister] = ip;
		auto [op, A, B, C] = instructions[ip];
		Execute(registers, op, A, B, C);

		// part 1
		//if (op == "eqrr")
		//{
		//	cout << registers[4] << '\n';
		//	break;
		//}

		// part 2
		if (op == "eqrr")
		{
			if (seenValues.count(registers[4]) == 0)
			{
				seenValues.insert(registers[4]);
				eqrrHitVals.push_back(registers[4]);
				
			}
			else
			{
				cout << eqrrHitVals.back() << '\n';
				break;
			}
		}



		ip = registers[boundRegister];
		++ip;
	}


	

	return 0;
}