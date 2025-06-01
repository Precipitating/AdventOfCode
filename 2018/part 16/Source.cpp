#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <set>
#include "operations.h"

struct Instruction
{
	vector<int> before;
	vector<int> opcodes;
	vector<int> after;
};

void Extract(const string& line, Instruction& tmp, vector<Instruction>& instructions)
{
	if (line[0] == 'B' || line[0] == 'A')
	{
		int start = line.find('[') + 1;

		while (start < line.size())
		{
			if (line[0] == 'B')
			{
				tmp.before.push_back(line[start] - '0');
			}
			else
			{
				tmp.after.push_back(line[start] - '0');
			}

			start += 3;
		}

		if (line[0] == 'A')
		{
			instructions.push_back(tmp);
			tmp = {};
		}
	}
	else
	{
		stringstream stream(line);
		int start = 0;

		while (stream >> start)
		{
			tmp.opcodes.push_back(start);
		}

	}
}


// part1 count check
int ProcessOperation(vector<int> before, const vector<int> &instructions, const vector<int>& target)
{
	int count = 0;
	if (addr(before, instructions) == target) ++count;
	if (addi(before, instructions) == target) ++count;
	if (mulr(before, instructions) == target) ++count;
	if (muli(before, instructions) == target) ++count;
	if (banr(before, instructions) == target) ++count;
	if (bani(before, instructions) == target) ++count;
	if (borr(before, instructions) == target) ++count;
	if (bori(before, instructions) == target) ++count;
	if (setr(before, instructions) == target) ++count;
	if (seti(before, instructions) == target) ++count;
	if (gtir(before, instructions) == target) ++count;
	if (gtri(before, instructions) == target) ++count;
	if (gtrr(before, instructions) == target) ++count;
	if (eqir(before, instructions) == target) ++count;
	if (eqri(before, instructions) == target) ++count;
	if (eqrr(before, instructions) == target) ++count;

	return count;

}

// part 2 pruning
void FindOpCode(vector<int> before, const vector<int>& instructions, const vector<int>& target, unordered_map<int, set<string>>& map)
{
	int currentOpCode = instructions[0];

	set<string> possibleCodes(map[currentOpCode].begin(), map[currentOpCode].end());


	if (possibleCodes.count("addr")) if (addr(before, instructions) != target) map[currentOpCode].erase("addr");
	if (possibleCodes.count("addi")) if (addi(before, instructions) != target) map[currentOpCode].erase("addi");
	if (possibleCodes.count("mulr")) if (mulr(before, instructions) != target) map[currentOpCode].erase("mulr");
	if (possibleCodes.count("muli")) if (muli(before, instructions) != target) map[currentOpCode].erase("muli");
	if (possibleCodes.count("banr")) if (banr(before, instructions) != target) map[currentOpCode].erase("banr");
	if (possibleCodes.count("bani")) if (bani(before, instructions) != target) map[currentOpCode].erase("bani");
	if (possibleCodes.count("borr")) if (borr(before, instructions) != target) map[currentOpCode].erase("borr");
	if (possibleCodes.count("bori")) if (bori(before, instructions) != target) map[currentOpCode].erase("bori");
	if (possibleCodes.count("setr")) if (setr(before, instructions) != target) map[currentOpCode].erase("setr");
	if (possibleCodes.count("seti")) if (seti(before, instructions) != target) map[currentOpCode].erase("seti");
	if (possibleCodes.count("gtir")) if (gtir(before, instructions) != target) map[currentOpCode].erase("gtir");
	if (possibleCodes.count("gtri")) if (gtri(before, instructions) != target) map[currentOpCode].erase("gtri");
	if (possibleCodes.count("gtrr")) if (gtrr(before, instructions) != target) map[currentOpCode].erase("gtrr");
	if (possibleCodes.count("eqir")) if (eqir(before, instructions) != target) map[currentOpCode].erase("eqir");
	if (possibleCodes.count("eqri")) if (eqri(before, instructions) != target) map[currentOpCode].erase("eqri");
	if (possibleCodes.count("eqrr")) if (eqrr(before, instructions) != target) map[currentOpCode].erase("eqrr");


}

// part 2 - find size 1 opcodes and remove it from all the other sets
// repeat until all 1 size
void EliminateKnownOpcodes(unordered_map<int, set<std::string>>& opCodesMap)
{
	bool changed;
	do 
	{
		changed = false;

		// find all opcodes with exactly one operation candidate
		set<string> assigned_ops;
		for (const auto& [opcode, ops] : opCodesMap)
		{
			if (ops.size() == 1) 
			{
				assigned_ops.insert(*ops.begin());
			}
		}

		// remove assigned operations from other opcode sets
		for (auto& [opcode, ops] : opCodesMap) 
		{
			if (ops.size() > 1) {
				for (const auto& assigned_op : assigned_ops) 
				{
					if (ops.erase(assigned_op) > 0) 
					{
						changed = true;
					}
				}
			}
		}
	} while (changed);
}

// part 2 - actual processing persist
void ProcessOperation2(const string& op, vector<int>& before, const vector<int>& instructions)
{
	if (op == "addr") before = addr(before, instructions);
	if (op == "addi") before = addi(before, instructions);
	if (op == "mulr") before = mulr(before, instructions);
	if (op == "muli") before = muli(before, instructions);
	if (op == "banr") before = banr(before, instructions);
	if (op == "bani") before = bani(before, instructions);
	if (op == "borr") before = borr(before, instructions);
	if (op == "bori") before = bori(before, instructions);
	if (op == "setr") before = setr(before, instructions);
	if (op == "seti") before = seti(before, instructions);
	if (op == "gtir") before = gtir(before, instructions);
	if (op == "gtri") before = gtri(before, instructions);
	if (op == "gtrr") before = gtrr(before, instructions);
	if (op == "eqir") before = eqir(before, instructions);
	if (op == "eqri") before = eqri(before, instructions);
	if (op == "eqrr") before = eqrr(before, instructions);

}

int main()
{
	fstream file("input.txt");
	string line;
	vector<Instruction> instructions;
	vector<vector<int>> testProgram;
	Instruction tmp;
	int whitespaceCount = 0;
	bool part2Input = false;
	int part1Count = 0;

	set<string> operationsSet = 
	{
		"addr",
		"addi",
		"mulr",
		"muli",
		"banr",
		"bani",
		"borr",
		"bori",
		"setr",
		"seti",
		"gtir",
		"gtri",
		"gtrr",
		"eqir",
		"eqri",
		"eqrr"
	};
	unordered_map<int, set<string>> opCodesMap;

	for (size_t i = 0; i < 16; ++i)
	{
		opCodesMap[i] = operationsSet;
	}





	// extract data
	while (getline(file, line))
	{
		if (line.empty())
		{
			++whitespaceCount;
			if (whitespaceCount > 1)
			{
				part2Input = true;

			}
			continue;
		}
		else
		{
			whitespaceCount = 0;
		}



		if (!part2Input)
		{
			Extract(line, tmp, instructions);
		}
		else
		{
			stringstream stream(line);
			int num;
			vector<int> nums;
			while (stream >> num)
			{
				nums.push_back(num);
			}
			testProgram.push_back(nums);
		}




	}

	// part1
	//for (const auto& instruction : instructions)
	//{
	//	if (ProcessOperation(instruction.before, instruction.opcodes, instruction.after) >= 3)
	//	{
	//		++part1Count;
	//	};
	//}

	// part 2
	for (const auto& instruction : instructions)
	{
		// initial prune
		FindOpCode(instruction.before, instruction.opcodes, instruction.after, opCodesMap);



	}

	for (const auto& instruction : instructions)
	{
		// initial prune
		FindOpCode(instruction.before, instruction.opcodes, instruction.after, opCodesMap);



	}
	EliminateKnownOpcodes(opCodesMap);

	// start simulation
	vector<int> startBefore = { 0,0,0,0 };

	for (size_t i = 0; i < testProgram.size(); ++i)
	{
		string op = *opCodesMap[testProgram[i][0]].begin();
		ProcessOperation2(op, startBefore, testProgram[i]);

	}





	//std::cout << part1Count;
	cout << startBefore[0];
	return 0;
}