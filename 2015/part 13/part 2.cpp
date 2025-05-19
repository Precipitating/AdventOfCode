#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <unordered_set>
#include <algorithm>

using namespace std;

struct Data
{
	int happiness = 0;
	string sittingPartner;


};


int main()
{
	std::ifstream file;
	multimap<string, Data> lookUpTable;
	/* find all unique names and store them in, will be used to store in vector*/
	unordered_set<std::string> names;
	vector<std::string> nameVector;
	string input;

	file.open("part2.txt");



	while (getline(file, input))
	{
		std::string tempName, gainOrLose;
		int happinessCount;
		Data currentLineData;

		/* remove the full stop to extract the name without it*/
		input.erase(input.end() - 1);
		stringstream stream(input);

		/* extract line and put in appropriate variables*/
		stream >> tempName;
		stream.ignore(std::numeric_limits<std::streamsize>::max(), 'd');
		stream >> gainOrLose;
		stream >> happinessCount;
		stream.ignore(std::numeric_limits<std::streamsize>::max(), 'o');
		stream >> currentLineData.sittingPartner;

		/* if we lose happiness then we will invert the happinessCount value*/
		if (gainOrLose.find("lose") != string::npos)
		{
			happinessCount *= -1;
		}

		currentLineData.happiness = happinessCount;

		names.insert(tempName);
		lookUpTable.insert(make_pair(tempName, currentLineData));


	}

	nameVector.insert(nameVector.end(), names.begin(), names.end());



	std::sort(nameVector.begin(), nameVector.end());

	int optimalRelations = -9999;
	do
	{
		int addedRelations = 0;

		for (int i = 0; i < nameVector.size(); ++i)
		{



			auto range = lookUpTable.equal_range(nameVector[i]);

			for (auto it = range.first; it != range.second; ++it)
			{
				if (i == 0)
				{
					if (it->second.sittingPartner == nameVector[nameVector.size() - 1])
					{
						addedRelations += it->second.happiness;
					}
					if (it->second.sittingPartner == nameVector[i + 1])
					{
						addedRelations += it->second.happiness;
					}
				}
				else if (i == nameVector.size() - 1)
				{
					if (it->second.sittingPartner == nameVector[0])
					{
						addedRelations += it->second.happiness;
					}
					if (it->second.sittingPartner == nameVector[i - 1])
					{
						addedRelations += it->second.happiness;
					}
				}
				else
				{


					if (it->second.sittingPartner == nameVector[i + 1])
					{
						addedRelations += it->second.happiness;
					}
					if (it->second.sittingPartner == nameVector[i - 1])
					{
						addedRelations += it->second.happiness;
					}

				}


			}

		}
		if (addedRelations > optimalRelations)
		{
			optimalRelations = addedRelations;
		}




	} while (std::next_permutation(nameVector.begin(), nameVector.end()));

	std::cout << optimalRelations;

	return 0;
}