#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <regex>
#include <unordered_set>
#include <queue>
#include "boost/container_hash/hash.hpp"

using namespace std;

struct Coords
{
	struct Hash
	{
		size_t operator()(const Coords& p) const
		{
			size_t seed = 0;
			boost::hash_combine(seed, p.coord.first);
			boost::hash_combine(seed, p.coord.second);
			boost::hash_combine(seed, p.steps);

			return seed;

		}
	};


	bool operator==(const Coords& other) const 
	{
		return coord == other.coord && steps == other.steps;
	}
	pair<int, int> coord = make_pair(0, 0);
	int steps = 0;

};

int main()
{
	fstream file; file.open("input.txt");
	string line;
	int x = 0; int y = 0; int z = 0;

	//pair<int, int> targetCoord = make_pair(0,0);

	vector<int> dist;

	while (getline(file, line))
	{
		line = regex_replace(line, regex(","), " ");
		stringstream stream(line);
		string currentDir;


		while (stream >> currentDir)
		{
			if (currentDir == "n")
			{
				y += 1;
				z -= 1;
			}
			else if (currentDir == "ne")
			{
				x += 1;
				z -= 1;
			}
			else if (currentDir == "nw")
			{
				x -= 1;
				y += 1;
			}
			else if (currentDir == "s")
			{
				y -= 1;
				z += 1;
			}
			else if (currentDir == "se")
			{
				x += 1;
				y -= 1;
			}
			else if (currentDir == "sw")
			{ 
				x -= 1;
				z += 1;
			}

			dist.push_back((abs(x) + abs(y) + abs(z)) / 2);
		}


	}

	//cout << (abs(x) + abs(y) + abs(z)) / 2;


	cout << *max_element(dist.begin(), dist.end());



	//Coords base;
	//unordered_set<Coords, Coords::Hash> visited;
	//queue<Coords> queue;
	//bool found = false;
	//queue.push(base);
	//visited.insert(base);

	//while (!queue.empty() && !found)
	//{
	//	Coords current = queue.front();
	//	queue.pop();

	//	if (current.coord == targetCoord)
	//	{
	//		found = true;
	//		cout << current.steps;
	//	}
	//	else
	//	{
	//		Coords tempCur = current;

	//		/* n */
	//		tempCur.coord.second += 1;






	//	}










	//}




	return 0;
}