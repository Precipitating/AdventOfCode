#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <numeric>
using namespace std;

enum TYPE
{
	None,
	Elf,
	Goblin
};
struct Object
{
	Object(TYPE type_) : type(type_) {}
	Object() = default;

	TYPE type = None;
	int health = 200;
	int attackPower = 3;

};

pair<int,int> hasAdjacentEnemy(const pair<int, int>& pos, const vector<pair<int, int>>& dir, map<pair<int, int>, Object>& npcs)
{
	pair<int, int> bestTarget = { -1,-1 };

	pair<int, int> lowestReadingOrder;
	int lowestHP = INT_MAX;
	for (const auto& dir : dir)
	{
		pair<int, int> adjacent = { pos.first + dir.first, pos.second + dir.second };

		auto it = npcs.find(adjacent);

		// if enemy and is adjacent...
		if (it != npcs.end() && npcs[adjacent].type != npcs[{pos.first, pos.second}].type)
		{
			int adjacentHP = it->second.health;
			if (adjacentHP < lowestHP || (lowestHP == adjacentHP && adjacent < bestTarget))
			{
				lowestHP = adjacentHP;
				bestTarget = adjacent;


			}
		}

	}

	return bestTarget;

}

pair<int, int>  BFS(pair<int, int> currentUnit, const vector<std::pair<int, int>>& directions, map<pair<int, int>, Object>& npcs, const set<pair<int, int>>& obstacles)
{
	int minDist = -1;
	map<pair<int, int>, int> potentialTargets;
	set<pair<int, int>> visited;
	map<pair<int, int>, int> distance;
	queue<pair<int, int>> queue;
	set<pair<int, int>> targetTiles;
	map<pair<int, int>, pair<int, int>> predecessor;
	queue.push(currentUnit);
	visited.insert(currentUnit);
	distance[currentUnit] = 0;


	// get all open tile coords around enemy units
	for (const auto& [coord, npc] : npcs)
	{
		if (npc.type != npcs[currentUnit].type)
		{
			for (const auto& dir : directions)
			{
				pair<int, int> adj = { coord.first + dir.first, coord.second + dir.second };

				// ignore tile if its blocked off by obstacle or another npc
				if (!obstacles.count(adj) && !npcs.count(adj))
				{
					targetTiles.insert(adj);
				}
			}
		}
	}

	while (!queue.empty())
	{
		pair<int, int> curr = queue.front(); queue.pop();


		if (targetTiles.count(curr))
		{
			potentialTargets[curr] = distance[curr];
			minDist = distance[curr];
		}

		// dont bother continuing if distance is higher, we already got a lower distance target
		if (minDist != -1 && distance[curr] > minDist) continue;

		// explore all adjacent directions
		for (const auto& dir : directions)
		{
			pair<int, int> next = { curr.first + dir.first, curr.second + dir.second };

			if (visited.count(next)) continue;
			if (obstacles.count(next)) continue;
			if (npcs.count(next)) continue;

			distance[next] = distance[curr] + 1;
			predecessor[next] = curr;
			queue.push(next);
			visited.insert(next);
		}
	}

	if (potentialTargets.empty())
		return currentUnit;  // no reachable targets, no move

	// find min distance utilizing map's default sorting as reading order
	// should be smallest coordinate with smallest distance
	auto smallestDist = min_element(potentialTargets.begin(), potentialTargets.end(), [](const auto& a, const auto& b)
		{
			// smallest distance priority, else smallest coordinate if distances are equal
			return (a.second != b.second) ? a.second < b.second : a.first < b.first;
		});

	pair<int, int> chosenTarget = smallestDist->first;


	// now get the optimal step by going through predecessors
	pair<int, int> bestStep = chosenTarget;

	while (predecessor[bestStep] != currentUnit)
	{
		bestStep = predecessor[bestStep];
	}

	npcs[bestStep] = npcs[currentUnit];
	npcs.erase(currentUnit);

	return bestStep;

	




}
int main()
{
	fstream file("input.txt");
	string line;
	map<pair<int, int>,Object > npcs;
	set<pair<int, int>> obstacles;
	vector<pair<int, int>> directions =
	{
		{-1, 0}, // up
		{0, -1}, // left
		{0, 1},  // right
		{1, 0}   // down
	};

	int elvesCount = 0;
	int goblinCount = 0;
	int round = 0;
	int row = 0;

	// part 2
	int elfAttack = 4;
	int elfCountFull = 0;
	int goblinCountFull = 0;
	map<pair<int, int>, Object > npcsCopy;

	// store input data in containers
	while (getline(file, line))
	{
		for (size_t i = 0; i < line.size(); ++i)
		{
			switch (line[i])
			{
			case 'G':
			{
				npcs[{row,i}] = Object(Goblin);
				++goblinCount;
				break;
			}
			case 'E':
			{
				npcs[{row, i}] = Object(Elf);
				++elvesCount;
				break;
			}
			case '#':
			{
				obstacles.insert({ row, i });
				break;
			}
			}
		}
		++row;

	}

	elfCountFull = elvesCount;
	goblinCountFull = goblinCount;
	npcsCopy = npcs;

#pragma region PART1
	//while (elvesCount > 0 && goblinCount > 0)
	//{
	//	set<pair<int, int>> movedThisRound;

	//	// get current top down order
	//	vector<pair<int, int>> turnOrder;
	//	for (const auto& [pos, _] : npcs)
	//	{
	//		turnOrder.push_back(pos);
	//	}

	//	// for each unit (reading order)
	//	for (const auto& pos : turnOrder)
	//	{
	//		if (movedThisRound.count(pos) || npcs.find(pos) == npcs.end())
	//			continue;

	//		// check if current unit next to enemy and attack if so
	//		pair<int,int> potentialAdjacent = hasAdjacentEnemy(pos, directions, npcs);
	//		if (potentialAdjacent != make_pair(-1,-1))
	//		{
	//			int adjacentHP = npcs[potentialAdjacent].health;
	//			TYPE adjacentType = npcs[potentialAdjacent].type;
	//			if (adjacentHP > 0)
	//			{
	//				npcs[potentialAdjacent].health -= npcs[pos].attackPower;

	//				if (npcs[potentialAdjacent].health <= 0)
	//				{
	//					npcs.erase(potentialAdjacent);
	//					
	//					goblinCount = (adjacentType == Goblin) ? goblinCount - 1 : goblinCount;
	//					elvesCount = (adjacentType == Elf) ? elvesCount - 1 : elvesCount;
	//				}

	//			}
	//			movedThisRound.insert(pos);

	//		}
	//		else
	//		{
	//			// else BFS towards nearest target and move a step
	//			auto newCoord = BFS(pos, directions, npcs, obstacles);
	//			movedThisRound.insert(newCoord);

	//			// try to attack if new position is adjacent
	//			potentialAdjacent = hasAdjacentEnemy(newCoord, directions, npcs);
	//			if (potentialAdjacent != make_pair(-1, -1))
	//			{
	//				int adjacentHP = npcs[potentialAdjacent].health;
	//				TYPE adjacentType = npcs[potentialAdjacent].type;
	//				if (adjacentHP > 0)
	//				{
	//					npcs[potentialAdjacent].health -= npcs[newCoord].attackPower;

	//					if (npcs[potentialAdjacent].health <= 0)
	//					{
	//						npcs.erase(potentialAdjacent);

	//						goblinCount = (adjacentType == Goblin) ? goblinCount - 1 : goblinCount;
	//						elvesCount = (adjacentType == Elf) ? elvesCount - 1 : elvesCount;
	//					}

	//				}
	//			}

	//		}




	//	}

	//	if (elvesCount > 0 && goblinCount > 0)
	//		++round;

	//}
#pragma endregion


#pragma region PART2
	while (goblinCount > 0)
	{
		set<pair<int, int>> movedThisRound;

		// get current top down order
		vector<pair<int, int>> turnOrder;
		for (const auto& [pos, _] : npcs)
		{
			turnOrder.push_back(pos);
		}

		// for each unit (reading order)
		for (const auto& pos : turnOrder)
		{
			if (movedThisRound.count(pos) || npcs.find(pos) == npcs.end())
				continue;

			// check if current unit next to enemy and attack if so
			pair<int, int> potentialAdjacent = hasAdjacentEnemy(pos, directions, npcs);
			if (potentialAdjacent != make_pair(-1, -1))
			{
				int adjacentHP = npcs[potentialAdjacent].health;
				TYPE adjacentType = npcs[potentialAdjacent].type;
				if (adjacentHP > 0)
				{
					npcs[potentialAdjacent].health -= npcs[pos].attackPower;

					if (npcs[potentialAdjacent].health <= 0)
					{
						if (adjacentType == Elf)
						{
							npcs = npcsCopy;
							round = -1;
							elvesCount = elfCountFull;
							goblinCount = goblinCountFull;
							++elfAttack;
							for (auto it = npcs.begin(); it != npcs.end(); ++it)
							{
								if (it->second.type == Elf)
								{
									it->second.attackPower = elfAttack;
								}
							}
							break;
						}
						npcs.erase(potentialAdjacent);

						goblinCount = (adjacentType == Goblin) ? goblinCount - 1 : goblinCount;
						

					}

				}
				movedThisRound.insert(pos);

			}
			else
			{
				// else BFS towards nearest target and move a step
				auto newCoord = BFS(pos, directions, npcs, obstacles);
				movedThisRound.insert(newCoord);

				// try to attack if new position is adjacent
				potentialAdjacent = hasAdjacentEnemy(newCoord, directions, npcs);
				if (potentialAdjacent != make_pair(-1, -1))
				{
					int adjacentHP = npcs[potentialAdjacent].health;
					TYPE adjacentType = npcs[potentialAdjacent].type;
					if (adjacentHP > 0)
					{
						npcs[potentialAdjacent].health -= npcs[newCoord].attackPower;

						if (npcs[potentialAdjacent].health <= 0)
						{
							if (adjacentType == Elf)
							{
								npcs = npcsCopy;
								round = -1;
								elvesCount = elfCountFull;
								goblinCount = goblinCountFull;
								++elfAttack;
								for (auto it = npcs.begin(); it != npcs.end(); ++it)
								{
									if (it->second.type == Elf)
									{
										it->second.attackPower = elfAttack;
									}
								}

								break;
							}

							npcs.erase(potentialAdjacent);

							goblinCount = (adjacentType == Goblin) ? goblinCount - 1 : goblinCount;

							
						}

					}
				}

			}




		}

		if (goblinCount > 0)
			++round;

	}
#pragma endregion

	cout << round * accumulate(npcs.begin(), npcs.end(),0, [](int acc, const auto& pair) {return acc + pair.second.health; });
	return 0;
}