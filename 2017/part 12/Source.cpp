#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <regex>
using namespace std;

void CheckKey(map<int, set<int>>& pipeline,int currentKey, int insideKey, set<int>& visited)
{
	visited.insert(insideKey);
	for (auto insideAgain : pipeline[insideKey])
	{
		pipeline[currentKey].insert(insideAgain);

	}

	for (auto insideAgain : pipeline[insideKey])
	{
		if (visited.count(insideAgain) != 1)
		{
			CheckKey(pipeline, currentKey, insideAgain,visited);
		}

	}




}

int main()
{
	fstream file; file.open("input.txt");
	string line;
	map<int, set<int>> pipeline;
	set<int> visited;
	int groupSize = 0;

	vector<int> others;
	while (getline(file, line))
	{
		line = regex_replace(line, regex("<->|,"), "");
		stringstream stream(line);
		int current = 0;
		stream >> current;

		int directCom = 0;
		
		while (stream >> directCom)
		{

			pipeline[current].insert(directCom);


		}



	}

	groupSize = pipeline.size();
	for (auto iter = pipeline.begin(); iter != pipeline.end(); ++iter)
	{
		int currentKey = iter->first;

		for (const int& inside : iter->second)
		{
			CheckKey(pipeline, iter->first, inside, visited);
			visited.clear();
		}

	}

	visited.clear();
	for (auto iter = pipeline.begin(); iter != pipeline.end(); ++iter)
	{
		set<int> insideSet = iter->second;
		int count = 0;

		if (visited.count(iter->first) == 0)
		{

			for (auto iter2 = pipeline.begin(); iter2 != pipeline.end(); ++iter2)
			{
				set<int> otherSet = iter2->second;

				if (iter->first != iter2->first)
				{
					if (insideSet == otherSet)
					{
						visited.insert(iter2->first);
						++count;
					}
				}


			}
		}
		groupSize -= count;



	}

	cout << pipeline[0].size() << '\n';
	cout << groupSize;
	return 0;
}