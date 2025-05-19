#include <iostream>
#include <nmmintrin.h>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>
#include <vector>
#include <tuple>
#include <map>
using namespace std;


struct Particle
{
	int id = -1;
	tuple<int, int, int> pos;
	tuple<int, int, int> vel;
	tuple<int, int, int> accel;

};

int ManhattanDistance(tuple<int,int,int> first, tuple<int,int,int> second)
{
	int x = 0, y = 0, z = 0;
	int x1 = 0, y1 = 0, z1 = 0;

	tie(x, y, z) = first;
	tie(x1, y1, z1) = second;

	return (abs(x - x1) + abs(y - y1) + abs(z- z1));

}

void NextStep(vector<Particle>& particles)
{

	for (int i = 0; i < particles.size(); ++i)
	{
		get<0>(particles[i].vel) += get<0>(particles[i].accel);
		get<1>(particles[i].vel) += get<1>(particles[i].accel);
		get<2>(particles[i].vel) += get<2>(particles[i].accel);

		get<0>(particles[i].pos) += get<0>(particles[i].vel);
		get<1>(particles[i].pos) += get<1>(particles[i].vel);
		get<2>(particles[i].pos) += get<2>(particles[i].vel);


	}
}

int main()
{
	regex fluffRemover("p|<|=|v|a|>");
	fstream file; file.open("input.txt");
	string line;
	Particle temp;
	vector<Particle> particles;
	vector<pair<int,int>> tempDistStorage;
	map<int, int> closerToParticle0;
	particles.reserve(1000);
	int id = 0;
	auto part1Particle = tuple<int, int, int>(0, 0, 0);


	while (getline(file, line))
	{
		line = regex_replace(line, fluffRemover, "");
		line = regex_replace(line, regex(","), " ");
		stringstream stream(line);
		stream >>	get<0>(temp.pos) >> get<1>(temp.pos) >> get<2>(temp.pos) >>
					get<0>(temp.vel) >> get<1>(temp.vel) >> get<2>(temp.vel) >>
					get<0>(temp.accel) >> get<1>(temp.accel) >> get<2>(temp.accel);

		temp.id = id;
		particles.push_back(temp);
		++id;

	}
	for (size_t i = 0; i < 1000000; ++i)
	{
		for (int j = 0; j< particles.size(); ++j)
		{
			auto& otherParticle = particles[j].pos;

			int dist = ManhattanDistance(part1Particle, otherParticle);
			tempDistStorage.push_back(make_pair(j,dist));


		}

		auto lowestDist = min_element(tempDistStorage.begin(), tempDistStorage.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) {return a.second < b.second; });

		if (lowestDist != tempDistStorage.end() && count_if(tempDistStorage.begin(), tempDistStorage.end(), [lowestDist](const pair<int,int>& a) {return a.second == lowestDist->second; }) == 1)
		{
			closerToParticle0[lowestDist->first] += 1;
		}



		tempDistStorage.clear();

		NextStep(particles);
	}

	auto maxElem = max_element(closerToParticle0.begin(), closerToParticle0.end(), [](const pair<int, int>& a, const pair<int, int>& b) {return a.second < b.second; });

	cout << maxElem->first;

	return 0;

}