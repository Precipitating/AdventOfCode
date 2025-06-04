#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <string>
#include <stack>
#include <queue>
using namespace std;


struct Point
{
	int x = 0, y = 0;

	bool operator==(const Point& other) const
	{
		return x == other.x && y == other.y;
	}
	bool operator<(const Point& other) const
	{
		return (y < other.y) || (y == other.y && x < other.x);
	}
};

struct PointHash
{
	size_t operator()(const Point& p) const 
	{
		return std::hash<int>()(p.x) ^ (std::hash<int>()(p.y) << 1);
	}
};

Point AddDoor(const Point& a, char dir, unordered_map<Point, unordered_set<Point, PointHash>, PointHash>& graph)
{
	Point next = a;

	switch (dir)
	{
	case 'N': --next.y; break;
	case 'E': ++next.x; break;
	case 'S': ++next.y; break;
	case 'W': --next.x; break;

	}

	graph[a].insert(next);
	graph[next].insert(a);

	return next;
}
int main()
{
	fstream file("input.txt");
	string line;
	unordered_map<Point,unordered_set<Point, PointHash>, PointHash> graph;
	getline(file, line);

	set<Point> currPoints = { Point()};
	stack<set<Point>> resultStack;
	stack<set<Point>> startStack;

	// bfs vars
	queue<Point> q;
	unordered_map<Point, int, PointHash> distance;
	q.push(Point());
	distance[Point()] = 0;


	// get all possible paths
	for (int i = 0; line[i] != '$'; ++i)
	{
		// handle directions
		switch (line[i])
		{
		case 'N':
		case 'E':
		case 'S':
		case 'W':
		{
			set<Point> nextPoints;
			for (const Point& p : currPoints)
			{
				Point next = AddDoor(p, line[i], graph);
				nextPoints.insert(next);
			}
			currPoints = move(nextPoints);

			break;
		}
		case '(':
			startStack.push(currPoints);
			resultStack.push({});
			break;
		case ')':
			resultStack.top().insert(currPoints.begin(), currPoints.end());
			currPoints = resultStack.top();
			startStack.pop();
			resultStack.pop();
			break;
		case '|':
			resultStack.top().insert(currPoints.begin(), currPoints.end());
			currPoints = startStack.top();
			break;
		}
	}


	// BFS
	while (!q.empty())
	{
		Point curr = q.front(); q.pop();

		// for each door in current coord, go thru the door
		for (const Point& door : graph[curr])
		{
			if (!distance.count(door))
			{
				distance[door] = distance[curr] + 1;
				q.push(door);
			}

		}

	}

	int part1Ans = 0;
	int part2Ans = 0;

	for (const auto& [p, d] : distance)
	{
		part1Ans = max(part1Ans, d);
		if (d >= 1000)
		{
			++part2Ans;
		}
	}

	cout << part1Ans << '\n';
	cout << part2Ans;
	return 0;
}