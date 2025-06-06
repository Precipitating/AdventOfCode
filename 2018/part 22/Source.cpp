#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <sstream>
#include <set>
#include <queue>
using namespace std;

enum class Gear
{
	NONE,
	CLIMBING,
	TORCH
};
enum RockType
{
	NONE,
	ROCKY,
	NARROW,
	WET
};

struct TravelData
{
	int x = 0, y = 0;
	Gear gear = Gear::TORCH;
	int minutes = 0;

	struct Compare
	{
		bool operator()(const TravelData& a, const TravelData& b) const
		{
			return a.minutes > b.minutes;
		}
	};
};
struct Data
{
	RockType rockType = RockType::NONE;
	int geologicalIdx = 0;
	int erosionLevel = 0;

};


vector<Gear> GetValidTools(RockType type)
{
	switch (type)
	{
	case ROCKY: return { Gear::TORCH, Gear::CLIMBING };
	case WET: return { Gear::CLIMBING, Gear::NONE };
	case NARROW: return { Gear::TORCH, Gear::NONE };
	}
}

bool ToolAllowed(Gear gear, RockType rockType)
{
	auto tools = GetValidTools(rockType);
	return find(tools.begin(), tools.end(), gear) != tools.end();

}

int main()
{
	fstream file("input.txt");
	string line;
	int depth = 0;
	pair<int, int> target = {};
	map<pair<int,int>, Data> coords;
	int part1Result = 0;

	// parse data
	while (getline(file, line))
	{
		if (line.find("depth: ") != string::npos)
		{
			string extracted = line.substr(line.find(' '));
			depth = stoi(extracted);
		}
		else
		{
			int x, y;
			char comma;
			string extracted = line.substr(line.find(' '));
			stringstream stream(extracted);
			stream >> x >> comma >> y;
			target = { x, y };

		}
	}


	// assign erosion, geologicalIdx and populate coords
	// can go outside the target, so add extra 50 incase
	Data temp;
	for (size_t x = 0; x <= target.first + 50; ++x)
	{
		for (size_t y = 0; y <= target.second + 50; ++y)
		{
			// calculate geoIdx
			if (x == 0 && y == 0 || x == target.first && y == target.second)
			{
				temp.geologicalIdx = 0;
			}
			else if (y == 0)
			{
				temp.geologicalIdx = x * 16807;
			}
			else if (x == 0)
			{
				temp.geologicalIdx = y * 48271;
			}
			else
			{
				temp.geologicalIdx = coords[{x - 1, y}].erosionLevel * coords[{x, y - 1}].erosionLevel;
			}

			// calculate erosion
			temp.erosionLevel = (temp.geologicalIdx + depth) % 20183;

			int calculateRockType = temp.erosionLevel % 3;

			switch (calculateRockType)
			{
			case 0: temp.rockType = RockType::ROCKY; break;
			case 1: temp.rockType = RockType::WET; part1Result += 1; break;
			case 2: temp.rockType = RockType::NARROW; part1Result += 2; break;
			}

			coords[{x,y}] = temp;

			temp = {};






		}
	}

	// part 1
	//cout << part1Result;


	// part 2
	// BFS
	priority_queue<TravelData, vector<TravelData>, TravelData::Compare> queue;
	queue.push({0,0,Gear::TORCH, 0});
	map<tuple<int,int,Gear>, int> visited;

	while (!queue.empty())
	{
		TravelData curr = queue.top(); queue.pop();
		// out of bounds
		if (curr.x < 0 || curr.y < 0 ) continue;

		// target reached
		if (curr.x == target.first && curr.y == target.second && curr.gear == Gear::TORCH)
		{
			cout << curr.minutes;
			break;
		}

		// don't continue if theres a better visited
		auto state = make_tuple(curr.x, curr.y, curr.gear);
		if (visited.count(state) && visited[state] <= curr.minutes) continue;
		visited[state] = curr.minutes;

		RockType currentRegion = coords[{curr.x, curr.y}].rockType;

		// switch gear to possible ones
		for (Gear gear : GetValidTools(currentRegion))
		{
			if (gear != curr.gear)
			{
				queue.push({ curr.x, curr.y, gear, curr.minutes + 7 });
			}
		}

		// move adjacent directions
		for (auto [x, y] : vector<pair<int, int>>{ {1,0},{-1,0},{0,1},{0,-1} })
		{
			int nextX = curr.x + x;
			int nextY = curr.y + y;

			if (nextX < 0 || nextY < 0) continue;

			RockType nextRegion = coords[{nextX, nextY}].rockType;

			if (ToolAllowed(curr.gear, nextRegion))
			{
				queue.push({ nextX, nextY, curr.gear, curr.minutes + 1 });
			}



		}




	

	}

	return 0;
}