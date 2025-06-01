#pragma once
#include <vector>
using namespace std;

#pragma region Arithmetic
vector<int> addr(vector<int> before, const vector<int>& opcodes)
{
	before[opcodes[3]] = before[opcodes[1]] + before[opcodes[2]];
	return before;
}

vector<int> addi(vector<int> before, const vector<int>& opcodes)
{
	before[opcodes[3]] = before[opcodes[1]] + opcodes[2];
	return before;
}

vector<int> mulr(vector<int> before, const vector<int>& opcodes)
{
	before[opcodes[3]] = before[opcodes[1]] * before[opcodes[2]];
	return before;
}
vector<int> muli(vector<int> before, const vector<int>& opcodes)
{
	before[opcodes[3]] = before[opcodes[1]] * opcodes[2];
	return before;
}
#pragma endregion

#pragma region BitWise
vector<int> banr(vector<int> before, const vector<int>& opcodes)
{
	before[opcodes[3]] = before[opcodes[1]] & before[opcodes[2]];
	return before;
}
vector<int> bani(vector<int> before, const vector<int>& opcodes)
{
	before[opcodes[3]] = before[opcodes[1]] & opcodes[2];
	return before;
}

vector<int> borr(vector<int> before, const vector<int>& opcodes)
{
	before[opcodes[3]] = before[opcodes[1]] | before[opcodes[2]];
	return before;
}

vector<int> bori(vector<int> before, const vector<int>& opcodes)
{
	before[opcodes[3]] = before[opcodes[1]] | opcodes[2];
	return before;
}

#pragma endregion

#pragma region Assignment
vector<int> setr(vector<int> before, const vector<int>& opcodes)
{
	before[opcodes[3]] = before[opcodes[1]];
	return before;
}
vector<int> seti(vector<int> before, const vector<int>& opcodes)
{
	before[opcodes[3]] = opcodes[1];
	return before;
}
#pragma endregion

#pragma region GreaterThan
vector<int> gtir(vector<int> before, const vector<int>& opcodes)
{
	before[opcodes[3]] = (opcodes[1] > before[opcodes[2]]) ? 1 : 0;
	return before;
}
vector<int> gtri(vector<int> before, const vector<int>& opcodes)
{
	before[opcodes[3]] = (before[opcodes[1]] > opcodes[2]) ? 1 : 0;
	return before;
}
vector<int> gtrr(vector<int> before, const vector<int>& opcodes)
{
	before[opcodes[3]] = (before[opcodes[1]] > before[opcodes[2]]) ? 1 : 0;
	return before;
}
#pragma endregion

#pragma region Equality
vector<int> eqir(vector<int> before, const vector<int>& opcodes)
{
	before[opcodes[3]] = (opcodes[1] == before[opcodes[2]]) ? 1 : 0;
	return before;
}
vector<int> eqri(vector<int> before, const vector<int>& opcodes)
{
	before[opcodes[3]] = (before[opcodes[1]] == opcodes[2]) ? 1 : 0;
	return before;
}
vector<int> eqrr(vector<int> before, const vector<int>& opcodes)
{
	before[opcodes[3]] = (before[opcodes[1]] == before[opcodes[2]]) ? 1 : 0;
	return before;
}
#pragma endregion