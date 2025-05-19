#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>
#include "Header.h"
#include <array>

using namespace std;

struct Node
{

	string name;
	int size = 0;
	int used = 0;
	int available = 0;
	int use = 0;

	vector<int> adjacentNodes;

};

pair<int, int> GetCoordinates(const string& input)
{
	regex nameFilter("[^0-9\s]");
	int x, y;
	string extractedString = input;
	extractedString = regex_replace(extractedString, nameFilter, " ");
	stringstream stream(extractedString); stream >> x >> y;

	return (make_pair(x, y));
}
void FindAdjacents(vector<Node>& nodes)
{
	for (Node& currentNode : nodes)
	{
		pair<int, int> currentCoord = GetCoordinates(currentNode.name);

		for (size_t i = 0; i < nodes.size(); ++i)
		{
			pair<int, int> adjacentList[4] =
			{
				make_pair(currentCoord.first + 1, currentCoord.second),
				make_pair(currentCoord.first - 1, currentCoord.second),
				make_pair(currentCoord.first, currentCoord.second + 1),
				make_pair(currentCoord.first, currentCoord.second - 1)
			};


			pair<int, int> currentCoord2 = GetCoordinates(nodes[i].name);

			for (int j = 0; j < 4; ++j)
			{
				if (currentCoord2 == adjacentList[j])
				{
					currentNode.adjacentNodes.push_back(i);
				}
			}




		}



	}
}

int FindViableNodes(const vector<Node>& vec)
{
	int result = 0;
	for (int i = 0; i < vec.size(); ++i)
	{
		for (int j = 0; j < vec.size(); ++j)
		{
			if (vec[i].name != vec[j].name && vec[i].used != 0 && (vec[j].available - vec[i].used) > 0)
			{
				++result;
			}

		}
	}
	return result;




}


void VisualizeMap(const vector<Node>& list)
{
	pair<int, int> maxCoord = GetCoordinates(list.back().name);
	array<array<char, 35>, 29> visualizedMap;

	for (const Node& current : list)
	{
		char type;
		pair<int, int> currentCoord = GetCoordinates(current.name);

		if (currentCoord.first == 0 && currentCoord.second == 0)
		{
			type = 'T';
		}
		else if (currentCoord.first == maxCoord.first && currentCoord.second == 0)
		{
			type = 'G';
		}
		else if (current.used == 0)
		{
			type = '_';
		}
		else if (current.used > 95)
		{
			type = '#';
		}
		else
		{
			type = '.';
		}

		visualizedMap[currentCoord.second][currentCoord.first] = type;


	}

	for (int i = 0; i < maxCoord.second + 1; ++i)
	{
		for (int j = 0; j < maxCoord.first + 1; ++j)
		{
			cout << visualizedMap[i][j];

		}
		cout << '\n';
	}

	/* 26 moves for empty next to GOAL data */

	/* 166 moves from empty to target */
	/* add up = 192 */

}

int main()
{
	fstream file; file.open("input.txt");
	string line;
	vector<Node> list;
	regex fluffRemover("T|%");


	while (getline(file, line))
	{
		if (line.find("/dev") != string::npos)
		{
			Node currentNode;
			line = regex_replace(line, fluffRemover, "");

			stringstream stream(line);
			stream >> currentNode.name >> currentNode.size >> currentNode.used >> currentNode.available >> currentNode.use;
			list.push_back(currentNode);
		}


	}

	//	FindAdjacents(list);
	//cout << FindViableNodes(list);
	VisualizeMap(list);


	return 0;
}