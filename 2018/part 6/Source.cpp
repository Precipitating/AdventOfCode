#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>
#include <set>

using namespace std;
#pragma region PART1
//int main()
//{
//	fstream file("input.txt");
//	string line;
//	vector<pair<int,int>> coords;
//	map<pair<int,int>, int> counter;
//	char comma;
//	int maxX = INT_MIN, maxY = INT_MIN;
//	
//
//	while (getline(file, line))
//	{
//		stringstream ss(line);
//		int x, y;
//		ss >> x >> comma >> y;
//		coords.emplace_back(x, y);
//		maxX = max(maxX, x);
//		maxY = max(maxY, y);
//
//	}
//	vector<vector<int>> grid(maxY + 1, vector<int>(maxX + 1));
//
//	for (int i = 0; i < grid.size(); ++i)
//	{
//		for (int j = 0; j < grid[i].size(); ++j)
//		{
//			int minDist = INT_MAX;
//			pair<int, int> lowestDist = { -1, -1 };
//
//			for (int k = 0; k < coords.size(); ++k)
//			{
//				int dist = abs(i - coords[k].first) + abs(j - coords[k].second);
//
//				if (dist < minDist)
//				{
//					lowestDist = coords[k];
//					minDist = dist;
//				}
//				else if (dist == minDist)
//				{
//					lowestDist = { -1, -1 };
//				}
//			}
//
//			if (lowestDist != std::pair<int, int>{-1, -1}) {
//				++counter[lowestDist];
//			}
//		}
//	}
//
//	set<pair<int, int>> infinite;
//	int width = maxX + 1;
//	int height = maxY + 1;
//
//	// Top and bottom edges
//	for (int x = 0; x < width; ++x) 
//	{
//		for (int y : {0, height - 1})
//		{
//			int minDist = INT_MAX;
//			pair<int, int> closest = { -1, -1 };
//			for (auto& c : coords) {
//				int d = abs(x - c.first) + abs(y - c.second);
//				if (d < minDist)
//				{
//					minDist = d;
//					closest = c;
//				}
//				else if (d == minDist) 
//				{
//					closest = { -1, -1 }; // tie
//				}
//			}
//			if (closest != pair<int, int>{-1, -1})
//				infinite.insert(closest);
//		}
//	}
//
//	// Left and right edges
//	for (int y = 0; y < height; ++y)
//	{
//		for (int x : {0, width - 1})
//		{
//			int minDist = INT_MAX;
//			pair<int, int> closest = { -1, -1 };
//			for (auto& c : coords)
//			{
//				int d = abs(x - c.first) + abs(y - c.second);
//				if (d < minDist)
//				{
//					minDist = d;
//					closest = c;
//				}
//				else if (d == minDist) {
//					closest = { -1, -1 }; // tie
//				}
//			}
//			if (closest != pair<int, int>{-1, -1})
//				infinite.insert(closest);
//		}
//	}
//
//	int maxArea = 0;
//	for (auto& [coord, count] : counter)
//	{
//		if (infinite.count(coord) == 0)
//		{
//			maxArea = max(maxArea, count);
//		}
//	}
//	cout << maxArea << endl;
//
//	return 0;
//}
#pragma endregion

#pragma region PART2
int main()
{
	fstream file("input.txt");
	string line;
	vector<pair<int, int>> coords;
	map<pair<int, int>, int> counter;
	char comma;
	int maxX = INT_MIN, maxY = INT_MIN;


	while (getline(file, line))
	{
		stringstream ss(line);
		int x, y;
		ss >> x >> comma >> y;
		coords.emplace_back(x, y);
		maxX = max(maxX, x);
		maxY = max(maxY, y);

	}
	vector<vector<int>> grid(maxY + 1, vector<int>(maxX + 1));


	int cntr = 0;
	for (int i = 0; i < grid.size(); ++i)
	{
		for (int j = 0; j < grid[i].size(); ++j)
		{
			int dist = 0;
			for (int k = 0; k < coords.size(); ++k)
			{
				dist += abs(i - coords[k].first) + abs(j - coords[k].second);

			}
			if (dist < 10000)
			{
				++cntr;
			}
		}
	}
	cout << cntr;
	

	return 0;
}
#pragma endregion