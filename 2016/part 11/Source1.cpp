#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include <vector>
#include <queue>
#include <array>
#include "combos.h"
#include <numeric>
#include <algorithm>
#include <unordered_set>

using namespace std;

enum Parts
{
	SG = 1,
	SM = -1,

	PG = 2,
	PM = -2,

	TG = 3,
	TM = -3,

	RG = 4,
	RM = -4,

	CG = 5,
	CM = -5,

	EG = 6,
	EM = -6,

	DG = 7,
	DM = -7

};

struct FloorPartCount
{
	pair<int, int> floor0 = make_pair(0, 0);
	pair<int, int> floor1 = make_pair(0, 0);
	pair<int, int> floor2 = make_pair(0, 0);
	pair<int, int> floor3 = make_pair(0, 0);

	int elevatorFloor = 0;

	size_t hash() const
	{
		size_t hashValue = 0;
		// Combine hash values directly without hash_combine
		hashValue ^= std::hash<int>{}(floor0.first) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2);
		hashValue ^= std::hash<int>{}(floor0.second) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2);
		hashValue ^= std::hash<int>{}(floor1.first) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2);
		hashValue ^= std::hash<int>{}(floor1.second) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2);
		hashValue ^= std::hash<int>{}(floor2.first) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2);
		hashValue ^= std::hash<int>{}(floor2.second) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2);
		hashValue ^= std::hash<int>{}(floor3.first) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2);
		hashValue ^= std::hash<int>{}(floor3.second) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2);
		hashValue ^= std::hash<int>{}(elevatorFloor)+  0x9e3779b9 + (hashValue << 6) + (hashValue >> 2);
		return hashValue;
	}

	bool operator==(const FloorPartCount& other) const {
		return floor0 == other.floor0 && floor1 == other.floor1 &&
			floor2 == other.floor2 && floor3 == other.floor3 &&
			elevatorFloor == other.elevatorFloor;;
	}

};
namespace std {
	template <>
	struct hash<FloorPartCount> {
		size_t operator()(const FloorPartCount& obj) const {
			return obj.hash();
		}
	};
}
struct State
{

	vector<vector<Parts>> stateVec;
	int elevatorLocation = 0;
	int steps = 0;
};



void BFS(const State& start, const vector<vector<Parts>>& goal);

/* get count of items/generators in the current vector. 1 = gen, 2 = chip */
int GetItemCount(const vector<Parts>& current, int type)
{
	int result = 0;

	auto countFunc = [type](const Parts& currentItem)
		{
			if (type == 1)
			{
				return (int)currentItem > 0;
			}
			else
			{
				return (int)currentItem < 0;
			}
		};

	result = count_if(current.begin(), current.end(), countFunc);


	return result;
}

bool isValid(const std::vector<Parts>& floors)
{
	bool result = false;

	const vector<Parts>& selected = floors;

	/* get count of chips/generators in this floor */
	int chipCount = GetItemCount(selected, 2);
	int generatorCount = GetItemCount(selected, 1);



	if (selected.empty())
	{
		result = true;

	}
	else
	{
		/* if only one type, valid */
		if (chipCount > 0 && generatorCount == 0)
		{
			result = true;
		}
		else if (chipCount == 0 && generatorCount > 0)
		{
			result = true;
		}

		/* check if there are matching pairs */

		if (result != true)
		{
			result = true;
		}
		for (int i = 0; i < selected.size(); ++i)
		{
			if ((int)selected[i] < 0)
			{
				/* if no matching pair.. and theres a generator its dead*/
				if (find(selected.begin(), selected.end(), -(int)selected[i]) == selected.end())
				{
					bool fried = false;
					for (int j = 0; j < selected.size() && !fried; ++j)
					{
						if (selected[j] > 0)
						{
							result = false;
							fried = true;
						}
					}

				}

			}
		}


	}


	return result;



}


int main()
{
	fstream file; file.open("input.txt");
	string line;
	regex fluffRemover("first|second|third|fourth|floor|contains|,|and|The");
	regex nextObject("\\ba\\b");
	State currentState;
	vector<std::vector<Parts>> floors;
	vector<std::vector<Parts>> goal;
	/* floor 1*/
	int elevatorFloor = 0;


	/* insert floor 1-4 Parts*/
	floors.insert(floors.end(), { SG,SM,PG,PM,EG,EM,DG,DM });
	floors.insert(floors.end(), { TG,RG,RM,CG,CM });
	floors.insert(floors.end(), { TM });
	floors.push_back({});

	currentState.stateVec = floors;
	currentState.elevatorLocation = 0;
	/* insert the goal we are trying to achieve */
	goal.push_back({});
	goal.push_back({});
	goal.push_back({});
	//goal.insert(goal.end(), { HM,LM,HG,LG });

	/*
		rules:
		elevator can take 2 items per stop
		elevator needs to take an object every time to operate
		a chip and its linked generator in same room = GOOD
		a chip with NO linked generator in same room WITH a different generator = BAD


	*/


	/* BFS */
	BFS(currentState, goal);
	//while (floors[3].size() != 10)
	//{
	//	Process(floors, elevatorFloor);
	//}





	return 0;
}
FloorPartCount countPartType(const State& start)
{
	int floor = 0;
	FloorPartCount result;




	for (int i = 0; i < start.stateVec.size(); ++i)
	{
		switch (i)
		{
		case 0:
			result.floor0.second = GetItemCount(start.stateVec[i], 1);
			result.floor0.first = GetItemCount(start.stateVec[i], 2);
			break;
		case 1:
			result.floor1.second = GetItemCount(start.stateVec[i], 1);
			result.floor1.first = GetItemCount(start.stateVec[i], 2);
			break;
		case 2:
			result.floor2.second = GetItemCount(start.stateVec[i], 1);
			result.floor2.first = GetItemCount(start.stateVec[i], 2);
			break;
		case 3:
			result.floor3.second = GetItemCount(start.stateVec[i], 1);
			result.floor3.first = GetItemCount(start.stateVec[i], 2);
			break;
		}
	}

	return result;

}
void ApplyNewState(State& current, vector< pair<Parts, Parts>> validPairs, vector<Parts> validSingles, unordered_set<FloorPartCount>& visited, queue<State>& queue, int type)
{
	if (type == 1 || type == 2)
	{
		if (type == 1)
		{

			for (int i = 0; i < validPairs.size(); ++i)
			{
				State newState = current;
				int currentElevator = current.elevatorLocation;

				newState.stateVec[currentElevator].erase(remove(newState.stateVec[currentElevator].begin(), newState.stateVec[currentElevator].end(), validPairs[i].first),
					newState.stateVec[currentElevator].end());
				newState.stateVec[currentElevator].erase(remove(newState.stateVec[currentElevator].begin(), newState.stateVec[currentElevator].end(), validPairs[i].second),
					newState.stateVec[currentElevator].end());

				newState.stateVec[currentElevator + 1].push_back(validPairs[i].first);
				newState.stateVec[currentElevator + 1].push_back(validPairs[i].second);
				++newState.steps;
				newState.elevatorLocation += 1;

				FloorPartCount count = countPartType(newState);
				count.elevatorFloor = current.elevatorLocation;
				if (visited.find(count) == visited.end())
				{
					queue.push(newState);
					visited.insert(count);
				}

			}

		}
		else
		{
			for (int i = 0; i < 1; ++i)
			{
				State newState = current;
				int currentElevator = current.elevatorLocation;

				newState.stateVec[currentElevator].erase(remove(newState.stateVec[currentElevator].begin(), newState.stateVec[currentElevator].end(), validSingles[i]),
					newState.stateVec[currentElevator].end());

				newState.stateVec[currentElevator + 1].push_back(validSingles[i]);
				++newState.steps;
				newState.elevatorLocation += 1;

				FloorPartCount count = countPartType(newState);
				count.elevatorFloor = current.elevatorLocation;
	
				if (visited.find(count) == visited.end())
				{
					queue.push(newState);
					visited.insert(count);
				}

			}
		}

	}
	else if (type == 3 || type == 4)
	{
		if (type == 3)
		{
			for (int i = 0; i < validSingles.size(); ++i)
			{
				State newState = current;
				int currentElevator = current.elevatorLocation;

				newState.stateVec[currentElevator].erase(remove(newState.stateVec[currentElevator].begin(), newState.stateVec[currentElevator].end(), validSingles[i]),
					newState.stateVec[currentElevator].end());

				newState.stateVec[currentElevator - 1].push_back(validSingles[i]);
				++newState.steps;
				newState.elevatorLocation -= 1;

				FloorPartCount count = countPartType(newState);
				count.elevatorFloor = current.elevatorLocation;


				if (visited.find(count) == visited.end())
				{
					queue.push(newState);
					visited.insert(count);
				}


			}
		}
		else
		{
			for (int i = 0; i < validPairs.size(); ++i)
			{
				State newState = current;
				int currentElevator = current.elevatorLocation;

				newState.stateVec[currentElevator].erase(remove(newState.stateVec[currentElevator].begin(), newState.stateVec[currentElevator].end(), validPairs[i].first),
					newState.stateVec[currentElevator].end());
				newState.stateVec[currentElevator].erase(remove(newState.stateVec[currentElevator].begin(), newState.stateVec[currentElevator].end(), validPairs[i].second),
					newState.stateVec[currentElevator].end());

				newState.stateVec[currentElevator - 1].push_back(validPairs[i].first);
				newState.stateVec[currentElevator - 1].push_back(validPairs[i].second);
				++newState.steps;
				newState.elevatorLocation -= 1;

				FloorPartCount count = countPartType(newState);
				count.elevatorFloor = current.elevatorLocation;

				if (visited.find(count) == visited.end())
				{
					queue.push(newState);
					visited.insert(count);
				}

			}
		}
	}


}
int NeighbourValidation(State& current, vector<pair<Parts, Parts>>& pairVec, vector<Parts>& singlePairs, vector<vector<Parts>> neighbourUp, vector<vector<Parts>> neighbourDown, unordered_set<FloorPartCount>& visited, queue<State>& queue)
{
	int result = 0;
	auto pairVecCopy = pairVec;
	auto singleVecCopy = singlePairs;
	bool neighbourUpValid = neighbourUp.size() > 0;
	bool neighbourDownValid = neighbourDown.size() > 0;
	vector<Parts> nextFloor;
	vector<Parts> prevFloor;

	vector<pair<Parts, Parts>> pairUpValids = pairVec;
	vector<Parts> singleUpValids = singlePairs;

	vector<pair<Parts, Parts>> pairDownValids = pairVec;
	vector<Parts> singleDownValids = singlePairs;


	if (neighbourUpValid) { nextFloor = neighbourUp[0]; }
	if (neighbourDownValid) { prevFloor = neighbourDown[0]; }

	/* prioritse going up, and if a pairs possible do it */
	/* remove bad pairs */
	if (neighbourUpValid)
	{
		for (auto it = pairVecCopy.begin(); it != pairVecCopy.end();)
		{
			/* reset the vector to its original state to prepare for next pair */
			nextFloor = neighbourUp[0];
			/* check the neighbours going up a floor */
			nextFloor.insert(nextFloor.end(), { it->first, it->second });

			if (!isValid(nextFloor))
			{
				pairUpValids.erase(remove(pairUpValids.begin(), pairUpValids.end(), *it), pairUpValids.end());
				++it;
			}

			if (isValid(nextFloor))
			{
				++it;
			}



		}

		result = 0;
		/* we checked the pairs, if there isnt any valid pairs after, then try single pairs going up */
		if (result == 0)
		{
			if (neighbourUpValid)
			{

				for (auto it = singleVecCopy.begin(); it != singleVecCopy.end();)
				{
					/* make sure nextFloor is reset */
					nextFloor = neighbourUp[0];

					nextFloor.push_back(*it);

					if (!isValid(nextFloor))
					{
						singleUpValids.erase(remove(singleUpValids.begin(), singleUpValids.end(), *it), singleUpValids.end());
						++it;
					}
					if (isValid(nextFloor))
					{
						++it;
					}


				}

			}

		}
	}

	result = 0;
	/* if thats also empty.. then we are forced to go down with priority to single then last resorting to pair downgrading */
	if (neighbourDownValid && result == 0)
	{

		for (auto it = singleVecCopy.begin(); it != singleVecCopy.end();)
		{
			prevFloor = neighbourDown[0];
			prevFloor.push_back(*it);

			if (!isValid(prevFloor))
			{
				singleDownValids.erase(remove(singleDownValids.begin(), singleDownValids.end(), *it), singleDownValids.end());
				++it;
			}

			if (isValid(prevFloor))
			{
				++it;
			}
		}

		result = 3;

		/* if after processing its empty again.. last resort is trying  pairs*/
		if (result == 3)
		{

			for (auto it = pairVecCopy.begin(); it != pairVecCopy.end();)
			{
				prevFloor = neighbourDown[0];

				prevFloor.insert(prevFloor.end(), { it->first, it->second });

				if (!isValid(prevFloor))
				{
					pairDownValids.erase(remove(pairDownValids.begin(), pairDownValids.end(), *it), pairDownValids.end());
					++it;
				}
				else
				{
					++it;
				}


			}

		}


	}

	/*
		TOP TO BOTTOM:
		apply pair UP
		apply single UP
		apply single DOWN
		apply pair DOWN

	*/


	if (pairUpValids.size() > 0 && current.elevatorLocation < 3)
		ApplyNewState(current, pairUpValids, singleUpValids, visited, queue, 1);

	if (pairUpValids.empty())
	{
		if (singleUpValids.size() > 0 && current.elevatorLocation < 3)
			ApplyNewState(current, pairUpValids, singleUpValids, visited, queue, 2);
	}

	bool fail = false;
	if (current.elevatorLocation > 0)
	{
		int emptyCount = 0;
		for (int i = 0; i < current.elevatorLocation; ++i)
		{
			if (current.stateVec[i].empty())
			{
				++emptyCount;
			}
		}
		if (emptyCount != current.elevatorLocation)
		{
			fail = true;
		}

	}

	if (fail)
	{
		if (singleDownValids.size() > 0 && current.elevatorLocation > 0)
			ApplyNewState(current, pairDownValids, singleDownValids, visited, queue, 3);
		if (pairDownValids.size() > 0 && current.elevatorLocation > 0)
			ApplyNewState(current, pairDownValids, singleDownValids, visited, queue, 4);
	}








	return result;


}




void BFS(const State& start, const vector<vector<Parts>>& goal)
{
	unordered_set<FloorPartCount> visited;
	queue<State> queue;
	queue.push(start);


	visited.insert(countPartType(start));




	while (!queue.empty())
	{
		auto current = queue.front();
		queue.pop();
		int elevatorLocation = current.elevatorLocation;

		vector<Parts>& currentFloor = current.stateVec[elevatorLocation];

		if (current.stateVec[3].size() == 14)
		{
			cout << current.steps;
			return;
		}

		/* get the floors nearby the current elevator location */
		vector<vector<Parts>> neighboursUp;
		vector<vector<Parts>> neighboursDown;
		if (elevatorLocation > 0)
		{
			neighboursDown.push_back(current.stateVec[elevatorLocation - 1]);
		}
		if (elevatorLocation < 3)
		{
			neighboursUp.push_back(current.stateVec[elevatorLocation + 1]);
		}

		/* get valid pair combos & singles */
		vector< pair<Parts, Parts>> validPairs;
		vector<Parts> validSingles;

		/* get all combinations of two pairs and remove invalids*/

		if (currentFloor.size() > 1)
		{
			typedef std::vector<Parts>::iterator Iter;
			for_each_combination(currentFloor.begin(), currentFloor.begin() + 2, currentFloor.end(),
				[&](Iter f, Iter l)
				{
					vector<Parts> tempPair;
					for (; f != l; ++f)
						tempPair.push_back(*f);
					auto pair = make_pair(tempPair[0], tempPair[1]);
					validPairs.push_back(pair);
					tempPair.clear();
					return false;
				}
			);

		}

		validSingles = currentFloor;

		/* check if current floors valid after simulating a move and if not, remove */
		for (int i = 0; i < validPairs.size(); ++i)
		{
			//vector<std::vector<Parts>> tempNeighbour = neighbours;
			std::vector<Parts> tempCurrentFloor = currentFloor;

			tempCurrentFloor.erase(remove(tempCurrentFloor.begin(), tempCurrentFloor.end(), validPairs[i].first), tempCurrentFloor.end());
			tempCurrentFloor.erase(remove(tempCurrentFloor.begin(), tempCurrentFloor.end(), validPairs[i].second), tempCurrentFloor.end());

			if (!isValid(tempCurrentFloor))
			{
				validPairs.erase(remove(validPairs.begin(), validPairs.end(), validPairs[i]), validPairs.end());
			}


		}

		/* do same with singles */
		for (int i = 0; i < validSingles.size(); ++i)
		{
			std::vector<Parts> tempCurrentFloor = currentFloor;

			tempCurrentFloor.erase(remove(tempCurrentFloor.begin(), tempCurrentFloor.end(), validSingles[i]), tempCurrentFloor.end());

			if (!isValid(tempCurrentFloor))
			{
				validSingles.erase(remove(validSingles.begin(), validSingles.end(), validSingles[i]), validSingles.end());
			}

		}

		/* 1 = pair up, 2 = single up, 3 = single down, 4 = pair down */
		int result = NeighbourValidation(current, validPairs, validSingles, neighboursUp, neighboursDown, visited, queue);





	}








}