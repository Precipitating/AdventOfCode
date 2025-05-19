#include <iostream>
#include <array>
#include <string>
#include <bitset>
#include <sstream>
#include <vector>
#include <fstream>
#include <sstream>
#include "Header.h"
#include <numeric>

using namespace std;


string CalculateHash(const string& input)
{
	vector<unsigned short> suffix{ 17, 31, 73, 47, 23 };
	vector<unsigned short> v(256);
	string result;
	for (unsigned short i = 0; i < list_max; ++i) v[i] = i;

	int shift = 0;
	int zero_index = 0;
	for (int j = 0; j < 64; ++j) {
		knothash(input, v, shift, zero_index);
		knothash(suffix, v, shift, zero_index);
	}

	for (int i = 0; i < 16; ++i) 
	{
		stringstream stream;
		unsigned short densehash = 0;
		for (int j = 0; j < 16; ++j)
		{
			densehash ^= v[i * 16 + j];
		}
		stream << hex << densehash;
		result.append(stream.str());
	}

	return result;

}
string CalculateHex(const string& input, int row)
{
	string hashInput = input + to_string(row);
	string hashed = CalculateHash(hashInput);
	string toHex;

	for (const char& letter : hashed)
	{
		switch (letter)
		{
		case '0': toHex.append("0000"); break;
		case '1': toHex.append("0001"); break;
		case '2': toHex.append("0010"); break;
		case '3': toHex.append("0011"); break;
		case '4': toHex.append("0100"); break;
		case '5': toHex.append("0101"); break;
		case '6': toHex.append("0110"); break;
		case '7': toHex.append("0111"); break;
		case '8': toHex.append("1000"); break;
		case '9': toHex.append("1001"); break;
		case 'a':
		case 'A': toHex.append("1010"); break;
		case 'b':
		case 'B': toHex.append("1011"); break;
		case 'c':
		case 'C': toHex.append("1100"); break;
		case 'd':
		case 'D': toHex.append("1101"); break;
		case 'e':
		case 'E': toHex.append("1110"); break;
		case 'f':
		case 'F': toHex.append("1111"); break;
		}

	}


	return toHex;
}

int main()
{
	


	/* ---------------------------------------------------- */

	string input = "amgozmfv";
	input += '-';
	array<array<int, 128>, 128> grid{ 0 };

	int part1Answer = 0;


	for (int i = 0; i < grid.size(); ++i)
	{
		string result = CalculateHex(input, i);

		for (int j = 0; j < result.size(); ++j)
		{
			int toNum = result[j] - '0';
			grid[i][j] = toNum;
		}
		part1Answer += count(grid[i].begin(), grid[i].end(), 1);

	}

	cout << part1Answer;

	return 0;
}