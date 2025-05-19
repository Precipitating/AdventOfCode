#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <numeric>
#include <unordered_set>
#include <stack>
#include <boost/container_hash/hash.hpp>

using namespace std;
#include "combinations.h"


struct Port
{
	bool operator==(const Port& other) const 
	{
		return this->port == other.port;
	}


	struct Hash
	{
		size_t operator()(const vector<Port>& prt) const
		{
			size_t seed = 0;

			for (const auto& vec : prt)
			{
				boost::hash_combine(seed, vec.port.first);
				boost::hash_combine(seed, vec.port.second);
			}




			return seed;

		}
	};
	pair<int, int> port = make_pair(0, 0);
	bool portAUsed = false;
	bool portBUsed = false;
	int length = 0;

};


bool ComparePort(Port& first, Port& second)
{
	bool result = false;


	if (first.port.first == second.port.first)
	{
		if (!first.portAUsed && !second.portAUsed)
		{
			first.portAUsed = true;
			second.portAUsed = true;
			result = true;
		}

	}
	if (first.port.first == second.port.second && !result)
	{
		if (!first.portAUsed && !second.portBUsed)
		{
			first.portAUsed = true;
			second.portBUsed = true;
			result = true;
		}
	}
	else if (first.port.second == second.port.first && !result)
	{
		if (!first.portBUsed && !second.portAUsed)
		{
			first.portBUsed = true;
			second.portAUsed = true;
			result = true;
		}

	}
	else if (first.port.second == second.port.second && !result)
	{

		if (!first.portBUsed && !second.portBUsed)
		{
			first.portBUsed = true;
			second.portBUsed = true;
			result = true;
		}
	}

	



	return result;

}



int main()
{
	fstream file; file.open("input.txt");
	string line;
	vector<Port> ports;
	queue<Port> zeroPorts;
	Port temp;

	while (getline(file, line))
	{
		replace(line.begin(), line.end(), '/', ' ');
		stringstream stream(line);
		int first, second;

		stream >> first >> second;

		temp.port = make_pair(first, second);
		ports.push_back(temp);

	}

	for (int i = 0; i < ports.size(); ++i)
	{
		if (ports[i].port.first == 0 || ports[i].port.second == 0)
		{
			zeroPorts.push(ports[i]);
		}
	}

	int maxStrength = 0;
	int currentStrength = 0;
	int maxLength = 0;

	ports.erase(remove_if(ports.begin(), ports.end(), [](const Port& prt) {return (prt.port.first == 0 || prt.port.second == 0); }));
	while (!zeroPorts.empty())
	{

		Port comparePort = zeroPorts.front();
		comparePort.length = 1;
		zeroPorts.pop();


		stack<Port> stack;
		stack.push(comparePort);
		
		unordered_set<vector<Port>, Port::Hash> visited;

		int currentPortMax = 0;

		currentStrength += comparePort.port.first;
		currentStrength += comparePort.port.second;
		vector<Port> dupes = { comparePort };
		while (!stack.empty())
		{
			Port& current = stack.top();


			if (visited.count(dupes) != 1)
			{
				visited.insert(dupes);
			}

			bool foundUnvisitedNode = false;

			for (int i = 0; i < ports.size(); ++i)
			{
				Port other = ports[i];
				auto whatIf = dupes; whatIf.push_back(other);

				if (visited.count(whatIf) == 0)
				{
					if (current.port != other.port)
					{
						if (ComparePort(current, other))
						{
							dupes.push_back(other);
							stack.push(other);

							currentStrength += other.port.first;
							currentStrength += other.port.second;

							foundUnvisitedNode = true;
							break;

						};
					}

				}


			}

			if (!foundUnvisitedNode)
			{
				maxStrength = max(maxStrength, currentStrength);
				maxLength = max(maxLength, (int)stack.size());
				
				int num = 0;

				currentStrength -= current.port.first;
				currentStrength -= current.port.second;

				(current.portAUsed) ? num = current.port.first : num = current.port.second;



				stack.pop();
				dupes.pop_back();

				if (stack.size() > 0)
				{
					(stack.top().port.first == num) ? stack.top().portAUsed = false : stack.top().portBUsed = false;
				}
				


			}



		}



	}




	std::cout << maxLength << '\n';
	std::cout << maxStrength;


	return 0;
}