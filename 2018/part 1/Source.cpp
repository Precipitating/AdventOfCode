#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
using namespace std;


int main()
{
	fstream file; file.open("input.txt");
	string line;
	int part1 = 0;


	while (getline(file, line))
	{
		stringstream stream(line);
		int num;

		stream >> num;

		part1 += num;


	}

	cout << part1;

	return 0;

}