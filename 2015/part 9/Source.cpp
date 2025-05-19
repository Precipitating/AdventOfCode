#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <utility>
#include <map>
#include <array>
#include <algorithm>
#include <regex>
#include "Header.h"

enum City : int
{
	AlphaCentauri,
	Snowdin,
	Tambi,
	Faerun,
	Norrath,
	Straylight,
	Tristram,
	Arbre

};

struct Schedule
{
	City currentLocation;
	City destination;
	int dist;

	
};


void Solve(std::vector<Schedule>& vec, std::vector<City> currentCombo, int& acceptResult)
{
	int lowestNum = 0;
	int cityVisted = 1;

	bool scheduleExists = false;

	for (int i = 0; i < 7; ++i)
	{
		if (scheduleExists)
			scheduleExists = false;
		City currentCity = currentCombo[0];
		City destination = currentCombo[1];

		for (int j = 0; (j < vec.size()) && !scheduleExists; ++j)
		{
			if ((vec[j].currentLocation == currentCity || vec[j].destination == currentCity) && !scheduleExists)
			{
				if ((vec[j].currentLocation == destination || vec[j].destination == destination) && !scheduleExists)
				{
					lowestNum += vec[j].dist;
					++cityVisted;
					currentCombo.erase(currentCombo.begin(), currentCombo.begin() + 1);
					scheduleExists = true;
				}

			}


		}



	}

	/*for (int i = 0; i < currentCombo.size() - 1; ++i)
	{
		if (scheduleExists)
			scheduleExists = false;

		for (int j = 0; (j < vec[currentCombo[i]].size() && !scheduleExists); ++j)
		{

			if (vec[currentCombo[i]][j].destination == currentCombo[i + 1])
			{
				lowestNum += vec[currentCombo[i]][j].dist;
				++cityVisted;
				scheduleExists = true;

			}


		}

	}

	*/

	if (cityVisted == 8)
	{
		/* get lowest distance*/
		//if (lowestNum < acceptResult)
		//{
		//	acceptResult = lowestNum;
		//}

		/* get highest distance*/
		if (lowestNum > acceptResult)
		{
			acceptResult = lowestNum;
		}
	}
}

int Calculate(std::vector<Schedule>& vec)
{
	/* use when getting lowest distance, we set high num so we can determine
		the smallest distance as we dont know the start value via line 96*/
	//int lowestNum = 1000;

	int lowestNum = 0;

	int comboCount = 0;

	std::vector<City> cityList = { AlphaCentauri, Snowdin, Tambi, Faerun, Norrath, Straylight, Tristram, Arbre };
	std::vector<City> currentCombo;
	currentCombo.reserve(8);

	for_each_permutation(cityList.begin(), cityList.begin() + 8, cityList.end(), [&](std::vector<City>::iterator f, std::vector<City>::iterator l)
		{
			for (; f != l; ++f)
				currentCombo.push_back(*f);

			Solve(vec, currentCombo, lowestNum);
			currentCombo.clear();
			return false;

		}
	);

	std::cout << lowestNum;


	return lowestNum;

}

void toEnum(const std::string& input, Schedule& currentSchedule, int startOrDest)
{

	if (startOrDest == 1)
	{
		if (input == "AlphaCentauri")	currentSchedule.currentLocation = AlphaCentauri;

		else if (input == "Snowdin")	currentSchedule.currentLocation = Snowdin;
		else if (input == "Tambi")		currentSchedule.currentLocation = Tambi;
		else if (input == "Faerun")		currentSchedule.currentLocation = Faerun;
		else if (input == "Norrath")	currentSchedule.currentLocation = Norrath;
		else if (input == "Straylight")	currentSchedule.currentLocation = Straylight;
		else if (input == "Tristram")	currentSchedule.currentLocation = Tristram;
		else if (input == "Arbre")		currentSchedule.currentLocation = Arbre;
	}
	else if (startOrDest == 2)
	{
		if (input == "AlphaCentauri")	currentSchedule.destination = AlphaCentauri;

		else if (input == "Snowdin")	currentSchedule.destination = Snowdin;
		else if (input == "Tambi")		currentSchedule.destination = Tambi;
		else if (input == "Faerun")		currentSchedule.destination = Faerun;
		else if (input == "Norrath")	currentSchedule.destination = Norrath;
		else if (input == "Straylight")	currentSchedule.destination = Straylight;
		else if (input == "Tristram")	currentSchedule.destination = Tristram;
		else if (input == "Arbre")		currentSchedule.destination = Arbre;


	}
}




int main()
{
	std::ifstream file;
	std::string line;
	std::vector<Schedule> schedule;
	std::vector<Schedule> currentLine;
	std::string currentLocation;
	std::string currentDestination;
	std::regex deleteFilter("\\bto\\b|=");
	std::string currentLoc;



	file.open("input.txt");


	/* parse into vector*/
	while (getline(file, line))
	{	
		/* delete all filler */
		line = std::regex_replace(line, deleteFilter, "");
		std::stringstream stream(line);
		
		
		/* parse current location, destination and distance into seperate variables*/
		Schedule currentSchedule;
		stream >> currentLocation >> currentDestination >> currentSchedule.dist;

		toEnum(currentLocation, currentSchedule, 1);
		toEnum(currentDestination, currentSchedule, 2);

		schedule.push_back(currentSchedule);
	}


	Calculate(schedule);

	return 0;

}


