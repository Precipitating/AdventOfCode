#include <iostream>
#include <unordered_set>
#include <array>
#include <sstream>
#include <fstream>
#include <utility>
#include <algorithm>

struct pair_hash {
	inline std::size_t operator()(const std::pair<int, int>& v) const {
		return v.first * 31 + v.second;
	}
};
int main()
{
	std::fstream file;

	std::pair<int, int> currentCoords = std::make_pair(0,0);

	std::unordered_set<std::pair<int, int>, pair_hash> santaCoordsHistory;
	santaCoordsHistory.insert(currentCoords);




	char c;
	file.open("input.txt", std::ios::in);

	/* read char by char*/
	while (file.get(c))
	{
		switch (c)
		{
		case '<':
			currentCoords.first -= 1;

			break;
		case '>':
			currentCoords.first += 1;

			break;
		case '^':
			currentCoords.second += 1;
			break;
		case 'v':
			currentCoords.second -= 1;
			break;
		}

		santaCoordsHistory.insert(currentCoords);



	}









	return 0;

}





