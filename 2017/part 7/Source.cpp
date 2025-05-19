#include <iostream>
#include <regex>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>


using namespace std;


struct Disc
{
	string name;
	int weight = 0;
	vector<string> holdingVec;



};
void CheckMatch(const string& target, const vector<Disc>& holdVec, int& count)
{
	for (int i = 0; i < holdVec.size(); ++i)
	{
		if (holdVec[i].name == target)
		{
			++count;

			if (holdVec[i].holdingVec.size() > 0)
			{
				for (int j = 0; j < holdVec[i].holdingVec.size(); ++j)
				{
					CheckMatch(holdVec[i].holdingVec[j], holdVec, count);
				}

			}
			break;

		}
	}

}
int main()
{
	fstream file; file.open("input.txt");
	string line;
	vector<Disc> discs;

	/* extract data to vector */
	while (getline(file, line))
	{
		Disc currentDisc;
		line.erase(remove_if(line.begin(), line.end(), [](char x) {return x == '(' || x == ')'; }), line.end());
		stringstream stream(line);
		stream >> currentDisc.name >> currentDisc.weight;

		if (line.find("->") != string::npos)
		{
			size_t arrowPos = line.find(">");
			line.erase(remove_if(line.begin(), line.end(), [](char x) {return x == '-' || x == '>' || x == ','; }), line.end());
			line = line.substr(arrowPos);
			stringstream stream2(line);
			string programsAbove;

			while (stream2 >> programsAbove)
			{
				currentDisc.holdingVec.push_back(programsAbove);
			}
		}

		discs.push_back(currentDisc);

	}

	/* find bottom program */
	vector<Disc> holdingDiscs;
	for (const Disc& elem : discs)
	{
		if (elem.holdingVec.size() > 0)
		{
			holdingDiscs.push_back(elem);
		}
	}

	Disc part1Answer;
	int mostStackedDisc = 0;
	for (int i = 0; i < holdingDiscs.size(); ++i)
	{
		Disc& current = holdingDiscs[i];
		int count = 0;
		for (const string& currentString : current.holdingVec)
		{
			CheckMatch(currentString, discs, count);


		}
		if (count > mostStackedDisc)
		{
			mostStackedDisc = count;
			part1Answer = current;
		}

	}

	cout << part1Answer.name;
	return 0;
}