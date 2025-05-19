#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <map>
using namespace std;

enum Direction : int
{
	UP = 1,
	DOWN = -1,
	LEFT = 2,
	RIGHT = -2
};

enum State
{
	NONE,
	WEAKENED,
	INFECTED,
	FLAGGED,
	CLEAN
};


struct Virus
{
	pair<int, int> pos = make_pair(0, 0);
	Direction dir = UP;

};



constexpr int PART_2_ITERATIONS = 10000000;

int main()
{
	fstream file; file.open("input.txt");
	string line;
	map<pair<int,int>,State> infectedPos1;
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
				infectedPos1[topLeft] = INFECTED;

			}

			++topLeft.first;
		}
		++topLeft.second;
		topLeft.first = -middleNum;

	}


	while (burstCount != PART_2_ITERATIONS)
	{

		bool exists = infectedPos1.count(virus.pos) == 1;
		/* if any state other than clean */
		if (exists)
		{
			switch (infectedPos1[virus.pos])
			{
			case INFECTED:
			{
				/* turn right */
				switch (virus.dir)
				{
				case UP: virus.dir = RIGHT;  break;
				case DOWN: virus.dir = LEFT;  break;
				case LEFT: virus.dir = UP;  break;
				case RIGHT: virus.dir = DOWN;  break;
				}

				infectedPos1[virus.pos] = FLAGGED;

			}
			break;
			case FLAGGED:
			{
				virus.dir = static_cast<Direction>(-static_cast<int>(virus.dir));

				infectedPos1[virus.pos] = CLEAN;

			}
			break;
			case WEAKENED:
			{
				infectedPos1[virus.pos] = INFECTED;
				++part1;
			}
			break;
			case CLEAN:
			{
				/* turn left */
				switch (virus.dir)
				{
				case UP: virus.dir = LEFT;  break;
				case DOWN: virus.dir = RIGHT;  break;
				case LEFT: virus.dir = DOWN;  break;
				case RIGHT: virus.dir = UP;  break;
				}

				infectedPos1[virus.pos] = WEAKENED;

			}
			break;
			}


		}
		else
		{
			/* if doesnt exist, its a clean, so make it weak */

			/* turn left */
			switch (virus.dir)
			{
			case UP: virus.dir = LEFT;  break;
			case DOWN: virus.dir = RIGHT;  break;
			case LEFT: virus.dir = DOWN;  break;
			case RIGHT: virus.dir = UP;  break;
			}

			infectedPos1[virus.pos] = WEAKENED;


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


	std::cout << part1;
	return 0;
}