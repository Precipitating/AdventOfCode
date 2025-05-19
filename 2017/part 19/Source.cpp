#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

const char DOWNUP = '|';
const char LEFTRIGHT = '-';
const char CORNER = '+';

enum DIRECTION
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

bool IsValidMove(DIRECTION dir, pair<int,int> pos, const vector<string>& map)
{
	bool result = false;
	int row = pos.first;
	int column = pos.second;


	switch (dir)
	{
	case UP:
	{
		if ((row - 1) < 0)
		{
			result = false;
		}
		else
		{
			if (map[row - 1][column] == ' ')
			{
				result = false;
			}
			else
			{
				result = true;
			}
		}

		break;
	}
	case DOWN:
		if ((row + 1) >= map.size())
		{
			result = false;
		}
		else
		{
			if (map[row + 1][column] == ' ')
			{
				result = false;
			}
			else
			{
				result = true;
			}
		}
		break;
	case LEFT:
		if ((column - 1) < 0)
		{
			result = false;
		}
		else
		{
			if (map[row][column - 1] == ' ')
			{
				result = false;
			}
			else
			{
				result = true;
			}
		}
		break;
	case RIGHT:
		if ((column + 1) >= map.size())
		{
			result = false;
		}
		else
		{
			if (map[row][column + 1] == ' ')
			{
				result = false;
			}
			else
			{
				result = true;
			}
		}
		break;

	}
	return result;
}

DIRECTION GetNewDir(DIRECTION& dir, pair<int, int>& pos, const vector<string>& map)
{
	DIRECTION newDir = dir;


	if (newDir == LEFT || newDir == RIGHT)
	{
		if (map[pos.first - 1][pos.second] != ' ')
		{
			newDir = UP;
		}
		else if (map[pos.first + 1][pos.second] != ' ')
		{
			newDir = DOWN;
		}
	}
	else if (newDir == UP || newDir == DOWN)
	{
		if (map[pos.first][pos.second - 1] != ' ')
		{
			newDir = LEFT;
		}
		else if (map[pos.first][pos.second + 1] != ' ')
		{
			newDir = RIGHT;
		}
	}

	return newDir;

}

void AddAlphabet(pair<int, int> pos, const vector<string>& map, string& result)
{
	char current = map[pos.first][pos.second];
	if (isalpha(current))
	{
		result.append(string(1,current));
	}
}


int main()
{
	fstream file; file.open("input.txt");
	string line;
	pair<int, int> currentPos = make_pair(0, 0);
	vector<string> maze;
	DIRECTION dir = DOWN;
	string result;

	while (getline(file, line))
	{
		maze.push_back(line);

	}

	int column = maze[0].find('|');

	currentPos = make_pair(0, column);

	while (result.size() != 10)
	{
		switch (dir)
		{
		case UP:
		{
			--currentPos.first;
			AddAlphabet(currentPos, maze, result);
			if (maze[currentPos.first][currentPos.second] == '+')
			{
				dir = GetNewDir(dir, currentPos, maze);
			}

			break;
		}
		case DOWN:
		{
			++currentPos.first;
			AddAlphabet(currentPos, maze, result);
			if (maze[currentPos.first][currentPos.second] == '+')
			{
				dir = GetNewDir(dir, currentPos, maze);
			}
			break;
		}
		case LEFT:
		{
			--currentPos.second;
			AddAlphabet(currentPos, maze, result);
			if (maze[currentPos.first][currentPos.second] == '+')
			{
				dir = GetNewDir(dir, currentPos, maze);
			}

			break;
		}
		case RIGHT:
		{
			++currentPos.second;
			AddAlphabet(currentPos, maze, result);
			if (maze[currentPos.first][currentPos.second] == '+')
			{
				dir = GetNewDir(dir, currentPos, maze);
			}

			break;
		}
		}
	}
	
	cout << result;

	return 0;
}
