#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

struct Data
{
	Data(pair<int, int> pos, pair<int, int> vel) : position(pos), velocity(vel) {}
	pair<int, int> position;
	pair<int, int> velocity;

};

void UpdatePositions(vector<Data>& data)
{
	for (auto& d : data)
	{
		d.position.first += d.velocity.first;
		d.position.second += d.velocity.second;
	}
}


void Render(const std::vector<Data>& points)
{
	if (points.empty()) return;

	int minX = INT_MAX, maxX = INT_MIN;
	int minY = INT_MAX, maxY = INT_MIN;

	// Find bounding box
	for (const auto& p : points)
	{
		if (p.position.first < minX) minX = p.position.first;
		if (p.position.first > maxX) maxX = p.position.first;
		if (p.position.second < minY) minY = p.position.second;
		if (p.position.second > maxY) maxY = p.position.second;
	}

	int width = maxX - minX + 1;
	int height = maxY - minY + 1;

	// Create grid and fill with spaces
	std::vector<std::string> grid(height, std::string(width, ' '));

	// Plot points as '#' on the grid
	for (const auto& p : points)
	{
		int x = p.position.first - minX;
		int y = p.position.second - minY;
		grid[y][x] = '#';
	}

	// Print the grid
	for (const auto& row : grid)
	{
		std::cout << row << '\n';
	}
}

int main()
{
	fstream file("input.txt");
	string line;
	vector<Data> data;
	vector<Data> bestData;


	// extract input to data
	while (getline(file, line))
	{
		Data tempData({ 0, 0 }, { 0, 0 });
		size_t posStart = line.find('<') + 1;
		size_t posEnd = line.find('>', posStart);

		size_t velStart = line.find('<', posEnd) + 1;
		size_t velEnd = line.find('>', velStart);

		string posStr = line.substr(posStart, posEnd - posStart);
		string velStr = line.substr(velStart, velEnd - velStart);

		int posX, posY, velX, velY;
		char comma;

		stringstream posStream(posStr);
		stringstream velStream(velStr);

		posStream >> posX >> comma >> posY;
		velStream >> velX >> comma >> velY;

		tempData.position.first = posX;
		tempData.position.second = posY;
		tempData.velocity.first = velX;
		tempData.velocity.second = velY;

		data.push_back(tempData);
	}


	long long smallest_area = LLONG_MAX;
	int time = 0;
	while (true)
	{
		++time;
		int minX = INT_MAX, maxX = INT_MIN;
		int minY = INT_MAX, maxY = INT_MIN;
		UpdatePositions(data);

		for (const auto& p : data)
		{
			if (p.position.first < minX) minX = p.position.first;
			if (p.position.first > maxX) maxX = p.position.first;
			if (p.position.second < minY) minY = p.position.second;
			if (p.position.second > maxY) maxY = p.position.second;
		}

		long long area = static_cast<long long>(maxX - minX + 1) * (maxY - minY + 1);


		if (area < smallest_area)
		{
			smallest_area = area;
			bestData = data;
		}
		else
		{
			break;
		}

	}
	Render(bestData);

	cout << time - 1;


	return 0;

}