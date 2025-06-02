#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

bool IsInBounds(int row, int col, const vector<string>& map)
{

	return row >= 0 && row < map.size() &&
		   col >= 0 && col < map[row].size();
}

bool HandleOpenAcre(int row, int col, const vector<string>& map)
{
	int count = 0;
	vector<pair<int, int>> directions =
	{
		{-1, 0},
		{+1, 0},
		{0, -1},
		{0,+1},
		{+1,+1},
		{+1,-1},
		{-1,+1},
		{-1,-1}
	};

	for (const pair<int, int>& dir : directions)
	{
		pair<int,int> adjacent = { row + dir.first, col + dir.second };
		if (IsInBounds(adjacent.first, adjacent.second, map))
		{
			if (map[adjacent.first][adjacent.second] == '|')
			{
				++count;
			}
		}

	}


	return count >= 3;


}

bool HandleTreeAcre(int row, int col, const vector<string>& map)
{
	int count = 0;
	vector<pair<int, int>> directions =
	{
		{-1, 0},
		{+1, 0},
		{0, -1},
		{0,+1},
		{+1,+1},
		{+1,-1},
		{-1,+1},
		{-1,-1}
	};

	for (const pair<int, int>& dir : directions)
	{
		pair<int, int> adjacent = { row + dir.first, col + dir.second };
		if (IsInBounds(adjacent.first, adjacent.second, map))
		{
			if (map[adjacent.first][adjacent.second] == '#')
			{
				++count;
			}
		}

	}


	return count >= 3;


}

bool HandleLumberYardAcre(int row, int col, const vector<string>& map)
{
	int lumberCount = 0;
	int treeCount = 0;
	vector<pair<int, int>> directions =
	{
		{-1, 0},
		{+1, 0},
		{0, -1},
		{0,+1},
		{+1,+1},
		{+1,-1},
		{-1,+1},
		{-1,-1}
	};

	for (const pair<int, int>& dir : directions)
	{
		pair<int, int> adjacent = { row + dir.first, col + dir.second };
		if (IsInBounds(adjacent.first, adjacent.second, map))
		{
			if (map[adjacent.first][adjacent.second] == '#')
			{
				++lumberCount;
			}
			else if (map[adjacent.first][adjacent.second] == '|')
			{
				++treeCount;
			}
		}

	}


	return (lumberCount >= 1 && treeCount >= 1);


}

void ProcessMinute(vector<string>& map)
{
	vector<string> mapCopy = map;

	for (size_t i = 0; i < map.size(); ++i)
	{
		for (size_t j = 0; j < map[0].size(); ++j)
		{
			switch (mapCopy[i][j])
			{
			case '.': map[i][j] = HandleOpenAcre(i, j, mapCopy) ? '|' :'.'; break;
			case '|': map[i][j] = HandleTreeAcre(i, j, mapCopy) ? '#' : '|';  break;
			case '#': map[i][j] = HandleLumberYardAcre(i, j, mapCopy) ? '#' : '.'; break;
			}

		}
	}


}

int main()
{
	fstream file("input.txt");
	vector<string> treeMap;
	unordered_map<string, int> seenMap;
	string line;
	int minutes = 0;

	int lumberCount = 0;
	int openSpacesCount = 0;
	int treeCount = 0;

	while (getline(file, line))
	{
		treeMap.push_back(line);

	}
	int totalMins = 1000000000;

	int minute = 0;
	vector<string> map = treeMap;

	while (minute < totalMins)
	{
		// Combine the map into a string key
		string combined;
		for (const string& row : map) 
		{
			combined += row;
		}

		// Cycle detection
		if (seenMap.count(combined))
		{
			int cycleStart = seenMap[combined];
			int cycleLength = minute - cycleStart;
			int remaining = totalMins - minute;
			int skip = remaining % cycleLength;

			// Simulate only the remaining needed steps
			for (int i = 0; i < skip; ++i)
			{
				ProcessMinute(map);
			}
			break; 
		}

		seenMap[combined] = minute;
		ProcessMinute(map);
		minute++;
	}


	for (const auto& row : map)
	{
		for (char ch : row)
		{
			if (ch == '#') ++lumberCount;
			else if (ch == '|') ++treeCount;
			else if (ch == '.') ++openSpacesCount;
		}
	}

	cout << lumberCount * treeCount;

	return 0;
}