#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <set>
#include <regex>
#include <stack>
using namespace std;

int minY = INT_MAX;
int maxY = INT_MIN;

void FlowIterative(int startX, int startY, const set<pair<int, int>>& clay, set<pair<int, int>>& settled, set<pair<int, int>>& flowing);

bool IsFlowing(int x, int y, const set<pair<int, int>>& flowing)
{
	return flowing.count({ x,y });
}
bool IsClay(int x, int y, const set<pair<int, int>>& clay)
{
	return clay.count({ x,y });
}
bool IsSettled(int x, int y, const set<pair<int, int>>& settled)
{
	return settled.count({ x,y });
}
bool IsSolid(int x, int y, const set<pair<int, int>>& clay, const set<pair<int, int>>& settled )
{
	return (clay.count({ x,y }) || settled.count({ x,y }));
}
bool SpreadSide(int x, int y, int dirX, const set<pair<int, int>>& clay,
	const set<pair<int, int>>& settled, set<pair<int, int>>& flowing,
	stack<pair<int, int>>& toProcess)
{
	while (true) {
		x += dirX;

		if (IsClay(x, y, clay))
			return true;  // Hit a wall (clay)

		flowing.insert({ x, y });  // Mark as flowing

		// If the space below is not solid, water can fall
		if (!IsSolid(x, y + 1, clay, settled)) {
			toProcess.push({ x, y });  // Process this cell again later
			return false;
		}
	}
}

void FlowIterative(int startX, int startY, const set<pair<int, int>>& clay, set<pair<int, int>>& settled, set<pair<int, int>>& flowing)
{
	stack<pair<int, int>> toProcess;
	toProcess.push({ startX, startY });

	while (!toProcess.empty()) 
	{
		auto [x, y] = toProcess.top();
		toProcess.pop();

		if (y > maxY) continue;
		if (IsSettled(x, y, settled)) continue;

		flowing.insert({ x,y });

		if (!IsSolid(x, y + 1, clay, settled))
		{
			toProcess.push({ x,y + 1 });
			continue;
		}

		bool leftBlocked = SpreadSide(x, y, -1, clay, settled, flowing, toProcess);
		bool rightBlocked = SpreadSide(x, y, +1, clay, settled, flowing, toProcess);

		if (leftBlocked && rightBlocked) {
			for (int dirX = x; !IsClay(dirX, y, clay); --dirX) 
			{
				settled.insert({ dirX, y });
				flowing.erase({ dirX, y });
			}
			for (int dirX = x + 1; !IsClay(dirX, y, clay); ++dirX)
			{
				settled.insert({ dirX, y });
				flowing.erase({ dirX, y });
			}
			toProcess.push({ x, y - 1 });  // Revisit above row to settle if possible
		}
	}
}
int main()
{
	fstream file("input.txt");
	string line;
	set<pair<int, int>> clay;
	set<pair<int, int>> flowing;
	set<pair<int, int>> settled;



	regex verticalRegex(R"(x=(\d+), y=(\d+)\.\.(\d+))");
	regex horizontalRegex(R"(y=(\d+), x=(\d+)\.\.(\d+))");
	smatch match;

	while (getline(file, line))
	{
		if (regex_match(line, match, verticalRegex))
		{
			int x = stoi(match[1]);
			int yStart = stoi(match[2]);
			int yEnd = stoi(match[3]);
			for (int y = yStart; y <= yEnd; ++y)
			{
				clay.emplace(x, y);
			}
			maxY = max(maxY, yEnd);
			minY = min(minY, yStart);
		}
		else if (regex_match(line, match, horizontalRegex))
		{
			int y = stoi(match[1]);
			int xStart = stoi(match[2]);
			int xEnd = stoi(match[3]);
			for (int x = xStart; x <= xEnd; ++x)
			{
				clay.emplace(x, y);
			}
			maxY = max(maxY, y);
			minY = min(minY, y);



		}

	}

	FlowIterative(500, 0, clay, settled, flowing);

	int result = 0;

	for (const auto& p : flowing)
	{
		if (p.second >= minY && p.second <= maxY)
			result++;
	}
	for (const auto& p : settled)
	{
		if (p.second >= minY && p.second <= maxY)
			result++;
	}



	cout << result << '\n';
	cout << settled.size();

	return 0;
}