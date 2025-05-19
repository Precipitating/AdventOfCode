#include <iostream>
#include <string>
#include <bitset>
using namespace std;


const int GEN_A_TEST = 65;
const int GEN_B_TEST = 8921;

const int GENERATOR_A_VAL = 873;
const int GENERATOR_B_VAL = 583;

const int GENERATOR_A_FACTOR = 16807;
const int GENERATOR_B_FACTOR = 48271;

const int GEN_A_MULTIPLE = 4;
const int GEN_B_MULTIPLE = 8;

const int REMAINDER_VAL = 2147483647;

const int PART_2_COUNTER = 5000000;

long long CalculateGen(long long prevVal, int factor, int multiple)
{
	long long result = prevVal;

	result *= factor;
	result %= REMAINDER_VAL;

	if ((result % multiple) != 0)
	{
		result = CalculateGen(result, factor, multiple);

	}

	return result;
}

int main()
{
	long long generatorA = GENERATOR_A_VAL;
	long long generatorB = GENERATOR_B_VAL;
	int count = 0;
	pair<string, string> binaryPair;

	for (int i = 0; i < PART_2_COUNTER; ++i)
	{
		generatorA = CalculateGen(generatorA, GENERATOR_A_FACTOR, GEN_A_MULTIPLE);
		generatorB = CalculateGen(generatorB, GENERATOR_B_FACTOR, GEN_B_MULTIPLE);

		binaryPair = make_pair(bitset<16>(generatorA).to_string(), bitset<16>(generatorB).to_string());

		if (binaryPair.first == binaryPair.second)
		{
			++count;
		}


	}


	cout << count;




}