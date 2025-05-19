#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_set>
#include <set>
#include <boost/functional/hash.hpp>
using namespace std;

struct Current
{

	bool operator==(const Current& other) const
	{
		bool result = false;


		if (visitedNumbers == other.visitedNumbers &&
			currentCoord == other.currentCoord)
		{
			result = true;
		}

		return result;

	}
	struct HashFunc
	{
		size_t operator()(const Current& b) const
		{
			size_t seed = 0;
			boost::hash_combine(seed, b.currentCoord);
			boost::hash_range(seed, b.visitedNumbers.begin(), b.visitedNumbers.end());
			//boost::hash_combine(seed, b.steps);
			//boost::hash_range(seed, b.map.begin(), b.map.end());
			return seed;

		}
	};

	vector<string> map;
	set<char> visitedNumbers;
	pair<int, int> currentCoord;
	int steps = 0;
	bool part2 = false;
};



bool isCharDigit(char x)
{
	return isdigit(x);
}

char ShortestDistance(pair<int, int> currentCoord, const vector <pair<int, pair<int, int>>>& coordList)
{
	char result = 'f';
	int shortestNum = 0;
	int prevDist = 999;

	for (int i = 1; i < coordList.size(); ++i)
	{
		int dist = abs(currentCoord.first - coordList[i].second.first) + abs(currentCoord.second - coordList[i].second.second);

		if (dist < prevDist)
		{
			prevDist = dist;
			result = coordList[i].first + '0';
			shortestNum = coordList[i].first;
		}




	}

	return result;
}

int main()
{
	fstream file; file.open("input.txt");
	vector<string> map;
	string line;
	Current defaultCurrent;
	vector <pair<int, pair<int, int>>> coordList;

	while (getline(file, line))
	{
		map.push_back(line);

	}
	defaultCurrent.map = map;
	defaultCurrent.visitedNumbers.insert('0');
	int numList[8] = { 0,1,2,3,4,5,6,7 };

	for (int i = 0; i < map.size(); ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			if (map[i].find(j + '0') != string::npos)
			{
				if (j == 0)
				{
					defaultCurrent.currentCoord.first = i;
					defaultCurrent.currentCoord.second = map[i].find(j + '0');
				}

				coordList.push_back(make_pair(j, make_pair(i, map[i].find(j + '0'))));
			}
		}

	}
	sort(coordList.begin(), coordList.end());

	unordered_set<Current, Current::HashFunc> visited;
	queue<Current> queue;
	queue.push(defaultCurrent);
	visited.insert(defaultCurrent);
	bool found = false;
	int result = 0;
	char shortest = 'f';
	int part1Lowest = 999;
	int part2Lowest = 999;
	while (!queue.empty() && !found)
	{
		Current current = queue.front();
		queue.pop();
		if (current.visitedNumbers.size() == 8)
		{

			if (current.part2)
			{
				if (part2Lowest > current.steps)
				{
					part2Lowest = current.steps;
				}
				found = true;
			}
			else
			{
				if (part1Lowest > current.steps)
				{
					part1Lowest = current.steps;
				}
				current.visitedNumbers.erase('0');
				current.part2 = true;
			}


		}

		if (!found)
		{
			pair<int, int> coords = current.currentCoord;

			Current modifiedCurrent = current;
			if (current.map[coords.first + 1][coords.second] != '#')
			{
				++modifiedCurrent.currentCoord.first;
				++modifiedCurrent.steps;
				if (isCharDigit(current.map[coords.first + 1][coords.second]))
				{
					if (current.visitedNumbers.find(current.map[coords.first + 1][coords.second]) == current.visitedNumbers.end())
					{
						modifiedCurrent.visitedNumbers.insert(current.map[coords.first + 1][coords.second]);
					}


				}

				if (visited.find(modifiedCurrent) == visited.end())
				{
					queue.push(modifiedCurrent);
					visited.insert(modifiedCurrent);
				}

				modifiedCurrent = current;

			}
			if (current.map[coords.first - 1][coords.second] != '#')
			{
				--modifiedCurrent.currentCoord.first;
				++modifiedCurrent.steps;
				if (isCharDigit(current.map[coords.first - 1][coords.second]))
				{
					if (current.visitedNumbers.find(current.map[coords.first - 1][coords.second]) == current.visitedNumbers.end())
					{
						modifiedCurrent.visitedNumbers.insert(current.map[coords.first - 1][coords.second]);
					}

				}

				if (visited.find(modifiedCurrent) == visited.end())
				{
					queue.push(modifiedCurrent);
					visited.insert(modifiedCurrent);
				}


				modifiedCurrent = current;

			}
			if (current.map[coords.first][coords.second + 1] != '#')
			{
				++modifiedCurrent.currentCoord.second;
				++modifiedCurrent.steps;
				if (isCharDigit(current.map[coords.first][coords.second + 1]))
				{
					if (current.visitedNumbers.find(current.map[coords.first][coords.second + 1]) == current.visitedNumbers.end())
					{
						modifiedCurrent.visitedNumbers.insert(current.map[coords.first][coords.second + 1]);
					}

				}

				if (visited.find(modifiedCurrent) == visited.end())
				{
					queue.push(modifiedCurrent);
					visited.insert(modifiedCurrent);
				}
				modifiedCurrent = current;

			}
			if (current.map[coords.first][coords.second - 1] != '#')
			{
				--modifiedCurrent.currentCoord.second;
				++modifiedCurrent.steps;
				if (isCharDigit(current.map[coords.first][coords.second - 1]))
				{
					if (current.visitedNumbers.find(current.map[coords.first][coords.second - 1]) == current.visitedNumbers.end())
					{
						modifiedCurrent.visitedNumbers.insert(current.map[coords.first][coords.second - 1]);
					}

				}

				if (visited.find(modifiedCurrent) == visited.end())
				{
					queue.push(modifiedCurrent);
					visited.insert(modifiedCurrent);
				}
				modifiedCurrent = current;

			}
		}










	}

	cout << part1Lowest << '\n';
	cout << part2Lowest << '\n';

	return 0;
}