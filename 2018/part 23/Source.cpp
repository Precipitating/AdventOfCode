#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Nanobot
{
	int x = 0, y = 0, z = 0;
	int radius = 0;
	int nanobotsInRange = 0;

};

struct Cube
{
	int x, y, z;
	int size;
	int botsInRange;
	int distToOrigin;

	// priority order: more bots -> closer to origin -> smaller size
	bool operator<(const Cube& other) const
	{
		if (botsInRange != other.botsInRange)
			return botsInRange < other.botsInRange;
		if (distToOrigin != other.distToOrigin)
			return distToOrigin > other.distToOrigin;
		return size > other.size;
	}
};

int ManhattanDistance(const vector<int>& source, const vector<int>& target)
{
	return abs(target[0] - source[0]) + abs(target[1] - source[1]) + abs(target[2] - source[2]);
}
int DistanceToCube(const Nanobot& bot, const Cube& cube)
{
	int dx = max(0, max(cube.x - bot.x, bot.x - (cube.x + cube.size - 1)));
	int dy = max(0, max(cube.y - bot.y, bot.y - (cube.y + cube.size - 1)));
	int dz = max(0, max(cube.z - bot.z, bot.z - (cube.z + cube.size - 1)));
	return dx + dy + dz;
}

int main()
{
	fstream file("input.txt");
	string line;
	vector<Nanobot> nanobots;


	while (getline(file, line))
	{
		string pos = line.substr(line.find('<') + 1);
		stringstream stream(pos);
		int x, y, z; char comma;
		stream >> x >> comma >> y >> comma >> z;
		int radius = stoi(line.substr(line.find("r=") + 2));
		nanobots.emplace_back(Nanobot{ x,y,z,radius, 0 });

	}


	for (int i = 0; i < nanobots.size(); ++i)
	{
		nanobots[i].nanobotsInRange = 0;
		for (int j = 0; j < nanobots.size(); ++j)
		{
			int dist = ManhattanDistance({ nanobots[i].x, nanobots[i].y, nanobots[i].z },
										 { nanobots[j].x, nanobots[j].y, nanobots[j].z });

			if (dist <= nanobots[i].radius)
			{
				++nanobots[i].nanobotsInRange;
			}
		}
	}

	auto comp = [](const Nanobot& a, const Nanobot& b)
		{
			return a.radius < b.radius;
		};

	// part 1
	//cout << max_element(nanobots.begin(), nanobots.end(), comp)->nanobotsInRange;


	// part 2
	int minCoord = INT_MAX, maxCoord = INT_MIN;

	// get min/max bounds of whole vec 
	for (const auto& bot : nanobots)
	{
		minCoord = min({ minCoord, bot.x - bot.radius, bot.y - bot.radius, bot.z - bot.radius });
		maxCoord = max({ maxCoord, bot.x + bot.radius, bot.y + bot.radius, bot.z + bot.radius });
	}

	// make it divisible by 2, expand to power of 2 to ensure this
	int size = 1;

	while (size < (maxCoord - minCoord)) size *= 2;

	// prio queue
	// start with a giant cube that covers all ranges
	priority_queue<Cube> pq;

	Cube start = { minCoord, minCoord, minCoord, size, 0, 0 };
	// how many bots does this cube cover?
	start.botsInRange = count_if(nanobots.begin(), nanobots.end(), [&](const Nanobot& bot)
		{
		return DistanceToCube(bot, start) <= bot.radius;
		});

	start.distToOrigin = abs(start.x) + abs(start.y) + abs(start.z);
	pq.push(start);


	// start algorithm - BFS
	// if 1x1x1 cube, we're done as it's a single coord
	// else split the cube to smaller parts and always get the next promising one

	while (!pq.empty())
	{
		Cube cube = pq.top(); pq.pop();

		// found 1x1x1 - answer
		if (cube.size == 1)
		{
			cout << cube.distToOrigin;
			break;
		}

		// split
		int half = cube.size / 2;

		// search the halved cube bound for nanobots
		// split to 8 cubes
		for (int dx : {0, half})
		{
			for (int dy : {0, half})
			{
				for (int dz : {0, half})
				{
					Cube sub = { cube.x + dx, cube.y + dy, cube.z + dz, half, 0, 0 };
					sub.botsInRange = count_if(nanobots.begin(), nanobots.end(), [&](const Nanobot& bot)
						{
							return DistanceToCube(bot, sub) <= bot.radius;
						});

					sub.distToOrigin = abs(sub.x) + abs(sub.y) + abs(sub.z);
					pq.push(sub);

				}
			}
		}



	}



	return 0;
}