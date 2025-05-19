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

const int REMAINDER_VAL = 2147483647;

const int PART_1_COUNTER = 40000000;

long long CalculateGen(long long prevVal, int factor)
{
	long long result = prevVal;

	result *= factor;
	result %= REMAINDER_VAL;

	return result;
}

int main()
{
	long long generatorA = GENERATOR_A_VAL;
	long long generatorB = GENERATOR_B_VAL;
	int count = 0;
	pair<string, string> binaryPair;

	for (int i = 0; i < PART_1_COUNTER; ++i)
	{
		generatorA = CalculateGen(generatorA, GENERATOR_A_FACTOR);
		generatorB = CalculateGen(generatorB, GENERATOR_B_FACTOR);

		binaryPair = make_pair(bitset<16>(generatorA).to_string(), bitset<16>(generatorB).to_string());

		if (binaryPair.first == binaryPair.second)
		{
			++count;
		}


	}


	cout << count;




}