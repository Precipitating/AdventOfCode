#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main()
{
	fstream file; file.open("input.txt");
	string line;
	vector<string> numbers;
	int total = 0;



	while (getline(file, line))
	{
		numbers.push_back(line);

	}

	int vecSize = numbers[0].size() / 2;
	for (size_t i = 0; i < numbers[0].size(); ++i)
	{

		char& currentChar = numbers[0][i];
		char nextChar;

		int nextCharOffset = vecSize + i;
		if (nextCharOffset > numbers[0].size() - 1)
		{
			nextChar = numbers[0][nextCharOffset - numbers[0].size()];
		}
		else
		{
			nextChar = numbers[0][nextCharOffset];
		}





		if (nextChar == currentChar)
		{
			total += currentChar - '0';
		}


	}
	cout << total;

	return 0;


}