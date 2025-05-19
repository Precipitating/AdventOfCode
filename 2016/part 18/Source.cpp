#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>


using namespace std;

bool isTrap(const string& currentRow, int idx)
{
	bool result = false;
	/* get left centre and right depending on idx */
	/* idx == 0 means left is always safe as its a wall */
	/* idx == (last element in string) means right is always safe as its a wall */
	char left = '?', centre = '?', right = '?';

	if (idx == 0) { left = '.'; }
	else { left = currentRow[idx - 1]; }

	if (idx + 1 == currentRow.size()) { right = '.'; }
	else { right = currentRow[idx + 1];}

	centre = currentRow[idx];

	/* conditions that if true means the current character is a trap */
	bool firstCondition = (left == '^' && centre == '^') && (right == '.');
	bool secondCondition = (centre == '^' && right == '^') && (left == '.');
	bool thirdCondition = (left == '^') && (right == '.' && centre == '.');
	bool fourthCondition = (right == '^') && (left == '.' && centre == '.');

	if (firstCondition || secondCondition || thirdCondition || fourthCondition)
	{
		result = true;
	}

	return result;



}

void CalculateNextRow(vector<string>& tileVec)
{
	string& currentRow = tileVec.back();
	string nextRow; nextRow.reserve(tileVec[0].size());

	/* calculate nextRow[0] */
	char& newFirst = currentRow[0];
	
	for (int i = 0; i < currentRow.size(); ++i)
	{
		if (isTrap(currentRow,i))
		{
			nextRow.append("^");
		}
		else
		{
			nextRow.append(".");
		}
	}

	tileVec.push_back(nextRow);





}

int main()
{
	fstream file; file.open("input.txt");
	string line;
	vector<string> tileVec;
	int rowNeeded = 40 - 1;
	int part2Row = 400000 - 1;

	while (getline(file, line))
	{
		tileVec.push_back(line);

	}

	for (int i = 0; i < part2Row; ++i)
	{
		CalculateNextRow(tileVec);
	}

	int safeTiles = 0;
	for (const string& currentRow : tileVec)
	{
		int safeCount = std::count(currentRow.begin(), currentRow.end(), '.');
		safeTiles += safeCount;
	}
	

	cout << safeTiles;
	return 0;
}

