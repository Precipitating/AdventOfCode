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
	bool destroyed = false;

};

bool CompareEquality (const tuple<int, int, int>& first, tuple<int, int, int> second)
{
	int x = 0, y = 0, z = 0;
	int x1 = 0, y1 = 0, z1 = 0;

	tie(x, y, z) = first;
	tie(x1, y1, z1) = second;

	return (x == x1 && y == y1 && z == z1);

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
	particles.reserve(1000);
	int id = 0;
	bool allCollisionsFound = false;

	while (getline(file, line))
	{
		line = regex_replace(line, fluffRemover, "");
		line = regex_replace(line, regex(","), " ");
		stringstream stream(line);
		stream >> get<0>(temp.pos) >> get<1>(temp.pos) >> get<2>(temp.pos) >>
			get<0>(temp.vel) >> get<1>(temp.vel) >> get<2>(temp.vel) >>
			get<0>(temp.accel) >> get<1>(temp.accel) >> get<2>(temp.accel);

		temp.id = id;
		particles.push_back(temp);
		++id;

	}


	while (!allCollisionsFound)
	{
		allCollisionsFound = true;

		for (int i = 0; i < 1000; ++i)
		{
			for (int i = 0; i < particles.size(); ++i)
			{
				tuple<int, int, int>& curr = particles[i].pos;
				int dupeCount = count_if(particles.begin(), particles.end(), [&](const Particle& other)
					{
						int x = 0, y = 0, z = 0;
						int x1 = 0, y1 = 0, z1 = 0;

						tie(x, y, z) = curr;
						tie(x1, y1, z1) = other.pos;

						return (x == x1 && y == y1 && z == z1);

					});

				if (dupeCount > 1)
				{
					allCollisionsFound = false;
					for (int j = 0; j < particles.size(); ++j)
					{
						if (!particles[j].destroyed)
						{
							int x = 0, y = 0, z = 0;
							int x1 = 0, y1 = 0, z1 = 0;

							tie(x, y, z) = curr;
							tie(x1, y1, z1) = particles[j].pos;

							if (x == x1 && y == y1 && z == z1)
							{
								particles[j].destroyed = true;
							}
						}


					}
				}


			}
			NextStep(particles);
		}



	}
	cout << count_if(particles.begin(), particles.end(), [](const Particle& particle) {return (!particle.destroyed); });



	return 0;

}