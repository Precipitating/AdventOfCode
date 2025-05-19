#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
using namespace std;

enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

struct Virus
{
	pair<int, int> pos = make_pair(0, 0);
	Direction dir = UP;

};

constexpr int PART_1_ITERATIONS = 10000;
int main()
{
	fstream file; file.open("input.txt");
	string line;
	set<pair<int, int>> infectedPos;
	int middleNum = 0;
	pair<int, int> topLeft;
	Virus virus;
	int part1 = 0;

	int burstCount = 0;


	/* get middle and positions of viruses with the middle being considered coord "0,0" */
	while (getline(file, line))
	{
		if (middleNum == 0)
		{
			middleNum = round(line.size() / 2);
			topLeft = make_pair(-middleNum, -middleNum);

		}

		stringstream stream(line);
		char currentChar;

		while (stream >> currentChar)
		{
			if (currentChar == '#')
			{
				infectedPos.insert(topLeft);
			}

			++topLeft.first;
		}
		++topLeft.second;
		topLeft.first = -middleNum;

	}


	while (burstCount != PART_1_ITERATIONS)
	{

		/* if infected */
		if (infectedPos.find(virus.pos) != infectedPos.end())
		{
			/* turn right */
			switch (virus.dir)
			{
			case UP: virus.dir = RIGHT;  break;
			case DOWN: virus.dir = LEFT;  break;
			case LEFT: virus.dir = UP;  break;
			case RIGHT: virus.dir = DOWN;  break;
			}

			/* disinfect current node */
			infectedPos.erase(virus.pos);


		}
		else
		{
			/* if clean do opposite */

			/* turn left */
			switch (virus.dir)
			{
			case UP: virus.dir = LEFT;  break;
			case DOWN: virus.dir = RIGHT;  break;
			case LEFT: virus.dir = DOWN;  break;
			case RIGHT: virus.dir = UP;  break;
			}

			/* infect current node */
			infectedPos.insert(virus.pos);

			++part1;
		}

		/* move forward */
		switch (virus.dir)
		{
		case UP: --virus.pos.second; break;
		case DOWN: ++virus.pos.second; break;
		case LEFT: --virus.pos.first; break;
		case RIGHT: ++virus.pos.first; break;

		}

		++burstCount;


	}


	cout << part1;
	return 0;
}