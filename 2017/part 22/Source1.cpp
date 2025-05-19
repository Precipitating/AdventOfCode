#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
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


struct Node
{
	pair<int, int> pos;
	mutable State state = NONE;

	bool operator<(const Node& other) const
	{
		return pos < other.pos;
	}
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
	set<Node> infectedPos;
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
		Node tempNode;

		while (stream >> currentChar)
		{
			if (currentChar == '#')
			{
				tempNode.pos = topLeft;
				tempNode.state = INFECTED;
				infectedPos.insert(tempNode);



			}

			++topLeft.first;
		}
		++topLeft.second;
		topLeft.first = -middleNum;

	}


	while (burstCount != PART_2_ITERATIONS)
	{

		auto it = find_if(infectedPos.begin(), infectedPos.end(), [virus](const Node& node) {return (node.pos == virus.pos );});
		/* if any state other than clean */
		if (it != infectedPos.end())
		{
			Node tempNode;
			tempNode.pos = virus.pos;
			switch (it->state)
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

				tempNode.state = FLAGGED;

				it->state = FLAGGED;

				infectedPos.erase(it);
				infectedPos.insert(tempNode);


			}
			break;
			case FLAGGED:
			{
				virus.dir = static_cast<Direction>(-static_cast<int>(virus.dir));
				tempNode.state = CLEAN;

				infectedPos.erase(it);
				infectedPos.insert(tempNode);

			}
			break;
			case WEAKENED:
			{
				tempNode.state = INFECTED;
				infectedPos.erase(it);
				infectedPos.insert(tempNode);
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

				tempNode.state = WEAKENED;

				infectedPos.erase(it);
				infectedPos.insert(tempNode);
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

			Node tempNode;
			tempNode.state = WEAKENED;
			tempNode.pos = virus.pos;

			/* make sure it doesnt exist already somehow */
			auto it2 = find_if(infectedPos.begin(), infectedPos.end(), [virus](const Node& node) {return (node.pos == virus.pos); });

			if (it != infectedPos.end())
			{
				infectedPos.erase(it);
			}
			else
			{
				infectedPos.insert(tempNode);
			}

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