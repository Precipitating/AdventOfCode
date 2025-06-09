#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

struct Coord
{
	int x = 0, y = 0, z = 0, w = 0;

};

int ManhattanDistance(const Coord& source, const Coord& target)
{
	auto [x1, y1, z1, w1] = source;
	auto [x2, y2, z2, w2] = target;

	return abs(x1 - x2) + abs(y1 - y2) +
		abs(z1 - z2) + abs(w1 - w2);
}


void DFS(int idx, const vector<Coord>& coords, vector<bool>& visited)
{
	visited[idx] = true;

	for (size_t i = 0; i < coords.size(); ++i)
	{
		if (!visited[i] && ManhattanDistance(coords[idx], coords[i]) <= 3)
		{
			DFS(i, coords, visited);
		}
	}

}


int CountConstellations(const vector<Coord>& coords)
{
	int count = 0;
	vector<bool> visited(coords.size(), false);

	for (size_t i = 0; i < coords.size(); ++i)
	{
		if (!visited[i])
		{
			DFS(i, coords, visited);
			++count;

		}
	}

	return count;


}
int main()
{
	fstream file("input.txt");
	string line;
	vector<Coord> coords;

	// parse data
	while (getline(file, line))
	{
		replace(line.begin(), line.end(), ',', ' ');
		stringstream stream(line);
		int x, y, z, w;
		stream >> x >> y >> z >> w;
		coords.emplace_back(Coord({ x,y,z,w }));


	}

	cout << CountConstellations(coords);


	return 0;
}