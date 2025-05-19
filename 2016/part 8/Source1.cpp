#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include <algorithm>
#include <array>

using namespace std;

void HandleRect(array<array<int, 50>, 6>& screen, int row, int column)
{

	for (int i = 0; i < column; ++i)
	{
		for (int j = 0; j < row; ++j)
		{
			screen[i][j] = 1;

		}
	}

}

void HandleColumn(array<array<int, 50>, 6>& screen, int column, int shiftDownBy)
{
	vector<int> rotatedColumn;


	for (int i = 0; i < 6; ++i)
	{
		rotatedColumn.push_back(screen[i][column]);

	}
	rotate(rotatedColumn.rbegin(), rotatedColumn.rbegin() + shiftDownBy, rotatedColumn.rend());


	for (int i = 0; i < 6; ++i)
	{
		screen[i][column] = rotatedColumn[i];
	}



}


void HandleRow(array<array<int, 50>, 6>& screen, int row, int shiftRightBy)
{


	rotate(screen[row].rbegin(), screen[row].rbegin() + shiftRightBy, screen[row].rend());






}
int main()
{
	array<array<int, 50>, 6> screen = { {{0}} };
	regex rectFilter("rect");
	regex columnFilter("column");
	regex rowFilter("row");
	smatch searchPos;
	fstream file; file.open("input.txt");
	string line;


	while (getline(file, line))
	{
		if (regex_search(line, searchPos, rectFilter))
		{
			int row, column;
			regex removeX("x");
			string extractedLine = line.substr(searchPos.position() + 4);
			extractedLine = regex_replace(extractedLine, removeX, " ");
			stringstream stream(extractedLine);

			stream >> row >> column;

			HandleRect(screen, row, column);

		}
		else if (regex_search(line, searchPos, columnFilter))
		{
			int row, shift;
			regex removeFluff("by|x|=|column");
			string extractedLine = line.substr(searchPos.position());
			extractedLine = regex_replace(extractedLine, removeFluff, "");
			stringstream stream(extractedLine);

			stream >> row >> shift;

			HandleColumn(screen, row, shift);

		}
		else if (regex_search(line, searchPos, rowFilter))
		{
			int row, shift;
			regex removeFluff("by|y|=|row");
			string extractedLine = line.substr(searchPos.position());
			extractedLine = regex_replace(extractedLine, removeFluff, "");
			stringstream stream(extractedLine);

			stream >> row >> shift;

			HandleRow(screen, row, shift);

		}



	}

	int count = 0;
	for (int i = 0; i < screen.size(); ++i)
	{
		for (int j = 0; j < 50; ++j)
		{
			if (j % 5 == 0)
			{
				cout << " ";
			}
			cout << screen[i][j];

		}
		cout << '\n';
	}


	return 0;
}