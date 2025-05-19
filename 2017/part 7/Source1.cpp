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
	// Define the equality operator for the custom class
	bool operator==(const int& other) const
	{
		return this->weightTotal == other;
	}
	string name;
	int weightTotal = 0;
	int weight = 0;
	vector<string> holdingVec;
	vector<Disc> holdingVecRef;



};


void CalculateWeight(Disc& current, const string& other)
{





}
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

void CheckMatchPt2(Disc& current, const vector<string>& target, vector<Disc>& discVec)
{
	for (int i = 0; i < target.size(); ++i)
	{
		const string& currentString = target[i];


		for (int j = 0; j < discVec.size(); ++j)
		{
			if (currentString == discVec[j].name)
			{
				current.weightTotal +=  discVec[j].weight;

				if (discVec[j].holdingVec.size() > 0)
				{
					for (int k = 0; k < discVec[k].holdingVec.size(); ++k)
					{
						for (int l = 0; l < discVec.size(); ++l)
						{
							if (discVec[l].name == discVec[k].holdingVec[k])
							{
								CheckMatchPt2(discVec[k], discVec[k].holdingVec, discVec);
							}
						}
					}
				}
			}


		}
	}


}


void CalculateTotal(Disc& current, vector<Disc>& holdingDiscs, const vector<Disc>& discs)
{
	if (current.weightTotal != current.weight)
	{
		return;
	}
	for (int i = 0; i < current.holdingVec.size(); ++i)
	{
		auto curr = current.holdingVec[i];

		if (find_if(holdingDiscs.begin(), holdingDiscs.end(), [&](const Disc& disc) {return disc.name == curr; }) == holdingDiscs.end())
		{
			auto it = find_if(discs.begin(), discs.end(), [&](const Disc& disc) {return disc.name == curr; });

			current.weightTotal += it->weight;

		}
		else
		{
			auto otherProgram = find_if(holdingDiscs.begin(), holdingDiscs.end(), [&](const Disc& disc) {return disc.name == curr; });
			if (otherProgram->weightTotal == otherProgram->weight)
			{
				CalculateTotal(*otherProgram, holdingDiscs, discs);
			}
			current.weightTotal += otherProgram->weightTotal;
			current.holdingVecRef.push_back(*otherProgram);
		}

		




	}
}

void FindImbalance(const vector<Disc>& holdingDisc, const Disc& root, int& targetValue, int& possibleImbalanceValue,int& currentWeight, bool &found)
{
	bool done = false;
	for (size_t i = 0; i < root.holdingVecRef.size(); ++i)
	{
		if (!found)
		{
		const Disc& current = root.holdingVecRef[i];
		int cnt = count(root.holdingVecRef.begin(), root.holdingVecRef.end(), root.holdingVecRef[i].weightTotal);
		currentWeight = root.holdingVecRef[i].weight;

			if (cnt == 1)
			{
				possibleImbalanceValue = root.holdingVecRef[i].weightTotal;
				if (i < root.holdingVecRef.size() - 1)
				{
					targetValue = root.holdingVecRef[i + 1].weightTotal;
				}
				else
				{
					targetValue = root.holdingVecRef[i -1].weightTotal;
				}

				FindImbalance(holdingDisc, root.holdingVecRef[i],targetValue,possibleImbalanceValue,currentWeight, found);

			}
			else if (cnt == root.holdingVecRef.size())
			{
				found = true;
				currentWeight = root.weight;
				return;
			}
			else
			{
				targetValue = root.holdingVecRef[i].weightTotal;


			}
		}

	}

	int correctOffset = possibleImbalanceValue - targetValue;

	int answer = currentWeight - correctOffset;

	if (currentWeight != 0)
	{
		std::cout << answer << '\n';
		currentWeight = 0;
		found = true;

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
		currentDisc.weightTotal = currentDisc.weight;
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

	cout << part1Answer.name << '\n';

	/* part 2 */


	for (int i = 0; i < holdingDiscs.size(); ++i)
	{
		Disc& current = holdingDiscs[i];

		CalculateTotal(current, holdingDiscs, discs);


	}

	auto root = find_if(holdingDiscs.begin(), holdingDiscs.end(), [&](const Disc& disc) {return disc.name == part1Answer.name; });

	int targetValue = 0;
	int possibleImbalanceValue = 0;
	int currentWeight = 0;
	bool found = false;
	FindImbalance(holdingDiscs, *root, targetValue, possibleImbalanceValue, currentWeight, found);

	return 0;
}