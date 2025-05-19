#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include "hashlibpp.h"
using namespace std;

constexpr int HIGHEST_BOUNDRY = 4;
constexpr int LOWEST_BOUNDRY = -1;


struct Current
{
	int x = 0;
	int y = 0;
	vector<char> path;
	int steps = 0;

	bool operator==(const Current& other) const 
	{
		return x == other.x && y == other.y && path == other.path && steps == other.steps;
	}
};

namespace std {
    template <>
    struct hash<Current> {
        size_t operator()(const Current& current) const {
            size_t hx = hash<int>()(current.x);
            size_t hy = hash<int>()(current.y);
            size_t hsteps = hash<int>()(current.steps);
            size_t hpath = 0;

            for (char c : current.path) {
                hpath = hpath * 31 + hash<char>()(c); // A simple hash combination, similar to what Java's String.hashCode() does
            }

            // Combine all hash values into one
            // This is a simple way to combine hash values, but you might want to use a more sophisticated method
            // to reduce the chances of collisions.
            return hx ^ (hy << 1) ^ (hpath << 2) ^ (hsteps << 3);
        }
    };
}

bool isOpen(char input)
{
    return (input == 'b' || input == 'c' || input == 'd' || input == 'e' || input == 'f');
}

bool isLegalPosition(char pos, const pair<int,int>& currentCoord )
{
    bool result = false;

    switch (pos)
    {
    case 'U':
        if ((currentCoord.second - 1) > LOWEST_BOUNDRY && (currentCoord.second - 1) < HIGHEST_BOUNDRY)
            result = true;
        break;
    case 'D':
        if ((currentCoord.second + 1) > LOWEST_BOUNDRY && (currentCoord.second + 1) < HIGHEST_BOUNDRY)
            result = true;
        break;
    case 'L':
        if ((currentCoord.first - 1) > LOWEST_BOUNDRY && (currentCoord.first - 1) < HIGHEST_BOUNDRY)
            result = true;
        break;
    case 'R':
        if ((currentCoord.first + 1) > LOWEST_BOUNDRY && (currentCoord.first + 1) < HIGHEST_BOUNDRY)
            result = true;
        break;
    }

    return result;
}


int main()
{
	string input = "rrrbmfta";
	string input2 = "ihgpwlah";
	hashwrapper* md5Wrap = new md5wrapper();

    Current start; start.path = { input.begin(), input.end() };
	unordered_set<Current> visited;
	queue<Current> queue;
    queue.push(start);
    visited.insert(start);
    bool found = false;

    /* use BFS to determine the shortest path */
    while (!queue.empty() && !found)
    {
        Current currentPos = queue.front();
        queue.pop();

        if (currentPos.x == 3 && currentPos.y == 3)
        {
            cout << string(currentPos.path.begin() + input.length(), currentPos.path.end()) << '\n';
            found = true;
        }

        /* get all possible combos and push it in, respecting the boundries */
        string hash = md5Wrap->getHashFromString(string(currentPos.path.begin(), currentPos.path.end()));
        hash = hash.substr(0,4);
        char& up = hash[0], down = hash[1], left = hash[2], right = hash[3];

        Current modifiedCurrent = currentPos;
        if (isOpen(up) && isLegalPosition('U', make_pair(currentPos.x, currentPos.y)))
        {
            modifiedCurrent.y -= 1;
            modifiedCurrent.path.push_back('U');
            ++modifiedCurrent.steps;
            if (visited.find(modifiedCurrent) == visited.end())
            {
                queue.push(modifiedCurrent);
                visited.insert(modifiedCurrent);
            }
            modifiedCurrent = currentPos;

        }
        if (isOpen(down)&& isLegalPosition('D', make_pair(currentPos.x, currentPos.y)))
        {
            modifiedCurrent.y += 1;
            modifiedCurrent.path.push_back('D');
            ++modifiedCurrent.steps;
            if (visited.find(modifiedCurrent) == visited.end())
            {
                queue.push(modifiedCurrent);
                visited.insert(modifiedCurrent);
            }
            modifiedCurrent = currentPos;
        }
        if (isOpen(left) && isLegalPosition('L', make_pair(currentPos.x, currentPos.y)))
        {
            modifiedCurrent.x -= 1;
            modifiedCurrent.path.push_back('L');
            ++modifiedCurrent.steps;
            if (visited.find(modifiedCurrent) == visited.end())
            {
                queue.push(modifiedCurrent);
                visited.insert(modifiedCurrent);
            }
            modifiedCurrent = currentPos;
        }
        if (isOpen(right) && isLegalPosition('R', make_pair(currentPos.x, currentPos.y)))
        {
            modifiedCurrent.x += 1;
            modifiedCurrent.path.push_back('R');
            ++modifiedCurrent.steps;
            if (visited.find(modifiedCurrent) == visited.end())
            {
                queue.push(modifiedCurrent);
                visited.insert(modifiedCurrent);
            }
            modifiedCurrent = currentPos;
        }


    }











    delete md5Wrap;
    md5Wrap = nullptr;



	return 0;
}