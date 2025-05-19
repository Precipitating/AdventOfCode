#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;


struct ReindeerData
{
	string name;
	int speed = 0;
	int maxSecondsTillRest = 0;
	int restTime = 0;
	int distanceTravelled = 0;


	int secondToRest = 0;
	int restCooldown = 0;

	int points = 0;


};





int main()
{
	ifstream file;
	string line;
	vector<ReindeerData> reindeers;

	file.open("input.txt");
	int timeLimit = 2503;


	while (getline(file, line))
	{
		ReindeerData tempData;
		stringstream stream(line);

		stream >> tempData.name;
		stream.ignore(std::numeric_limits<std::streamsize>::max(), 'y');
		stream >> tempData.speed;
		stream.ignore(std::numeric_limits<std::streamsize>::max(), 'r');
		stream >> tempData.maxSecondsTillRest;
		stream.ignore(std::numeric_limits<std::streamsize>::max(), 'r');
		stream.ignore(std::numeric_limits<std::streamsize>::max(), 'r');
		stream >> tempData.restTime;

		reindeers.push_back(tempData);

	}

	std::vector<int> distances;
	for (int i = 0; i < timeLimit; ++i)
	{
		for (auto& reindeer : reindeers)
		{
			if (reindeer.secondToRest == reindeer.maxSecondsTillRest)
			{
				reindeer.restCooldown = reindeer.restTime;
				reindeer.secondToRest = 0;
			}


			if (reindeer.restCooldown <= 0)
			{
				++reindeer.secondToRest;
				reindeer.distanceTravelled += reindeer.speed;


			}
			else
			{
				--reindeer.restCooldown;
			}
















		}



		std::vector<int> tempDistances;
		for (int j = 0; j < reindeers.size(); ++j)
		{
			tempDistances.push_back(reindeers[j].distanceTravelled);

		}

		int highestDistance = *std::max_element(tempDistances.begin(), tempDistances.end());


		for (int i = 0; i < reindeers.size(); ++i)
		{
			if (reindeers[i].distanceTravelled == highestDistance)
			{
				++reindeers[i].points;
			}
		}





	}



	return 0;

}