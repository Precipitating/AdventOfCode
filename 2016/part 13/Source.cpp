#include <iostream>
#include <unordered_set>
#include <queue>
#include <utility>
#include <bitset>
#include <algorithm>

using namespace std;

struct Coordinates
{
	pair<int, int> coords = make_pair(1, 1);
	int steps = 0;

	bool isValid()
	{
		bool result = false;
		
		int formula = (coords.first * coords.first) + (3 * coords.first) + (2 * coords.first * coords.second) + (coords.second) + (coords.second * coords.second);

		int puzzleInput = 1352;

		formula += puzzleInput;

		string toBinary = bitset<16>(formula).to_string();

		int countOnes = count_if(toBinary.begin(), toBinary.end(), [](const char& currentChar) {return (currentChar == '1'); });

		result = (countOnes % 2) == 0;

		return result;
	}

	bool operator==(const Coordinates& other) const {
		return coords == other.coords && steps == other.steps;
	}

	struct HashFunc
	{
		size_t operator()(const Coordinates& coord) const
		{
			size_t hashValue = hash<int>()(coord.coords.first);
			hashValue ^= hash<int>()(coord.coords.second) << 1;
			hashValue ^= std::hash<int>()(coord.steps) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2);

			return hashValue;
		}
	};




};


int main()
{
	unordered_set<Coordinates, Coordinates::HashFunc> visited;
	queue<Coordinates> queue;
	queue.push(Coordinates());
	visited.insert(Coordinates());
	bool found = false;
	while (!queue.empty() && !found)
	{
		Coordinates current = queue.front();
		queue.pop();

		if (current.coords == make_pair(31, 39))
		{
			cout << current.steps << '\n';
			found = true;
		}

		/* check if adding 1 to x coord is valid, and if so push to queue */
		Coordinates tempCoord = current;
		tempCoord.coords.first += 1;
		if (tempCoord.isValid())
		{
			++tempCoord.steps;
			if (visited.find(tempCoord) == visited.end())
			{
				queue.push(tempCoord);
				visited.insert(tempCoord);
			}
		}

		/* check if adding 1 to y coord is valid, and if so push to queue */
		tempCoord = current;
		tempCoord.coords.second += 1;
		if (tempCoord.isValid())
		{
			++tempCoord.steps;
			if (visited.find(tempCoord) == visited.end())
			{
				queue.push(tempCoord);
				visited.insert(tempCoord);
			}
		}

		/* check if subtracting 1 to y coord is valid, and if so push to queue */
		tempCoord = current;
		tempCoord.coords.second -= 1;
		if (tempCoord.coords.second >= 0)
		{
			if (tempCoord.isValid())
			{
				++tempCoord.steps;
				if (visited.find(tempCoord) == visited.end())
				{
					queue.push(tempCoord);
					visited.insert(tempCoord);
				}
			}
		}

		/* check if subtracting 1 to x coord is valid, and if so push to queue */
		tempCoord = current;
		tempCoord.coords.first -= 1;
		if (tempCoord.coords.first >= 0)
		{
			if (tempCoord.isValid())
			{
				++tempCoord.steps;
				if (visited.find(tempCoord) == visited.end())
				{
					queue.push(tempCoord);
					visited.insert(tempCoord);
				}
			}
		}




	}




}