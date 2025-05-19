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
	int portA = 0;
	int portB = 0;
	bool portUsed = false;
	int length = 0;

};


//bool ComparePort(Port& first, Port& second)
//{
//	bool result = false;
//
//
//	if (first.port.first == second.port.first)
//	{
//		if (!first.portAUsed && !second.portAUsed)
//		{
//			first.portAUsed = true;
//			second.portAUsed = true;
//			result = true;
//		}
//
//	}
//	if (first.port.first == second.port.second && !result)
//	{
//		if (!first.portAUsed && !second.portBUsed)
//		{
//			first.portAUsed = true;
//			second.portBUsed = true;
//			result = true;
//		}
//	}
//	else if (first.port.second == second.port.first && !result)
//	{
//		if (!first.portBUsed && !second.portAUsed)
//		{
//			first.portBUsed = true;
//			second.portAUsed = true;
//			result = true;
//		}
//
//	}
//	else if (first.port.second == second.port.second && !result)
//	{
//
//		if (!first.portBUsed && !second.portBUsed)
//		{
//			first.portBUsed = true;
//			second.portBUsed = true;
//			result = true;
//		}
//	}
//
//
//
//
//
//	return result;
//
//}

int maxStrength = 0;
int maxLongestStrength = 0;
int maxLength = 0;

void Process(int next, int maxLen, int strength, vector<Port>& ports)
{
	maxStrength = std::max(maxStrength, strength);

	maxLength = std::max(maxLength, maxLen);



	if (maxLength == maxLen)
	{
		maxLongestStrength = std::max(maxLongestStrength, strength);

	}

	for (auto& port : ports)
	{
		int nextNum = -1;


		if ((!port.portUsed) && (port.portA == next || port.portB == next))
		{
			((port.portA == next) ? nextNum = port.portB : nextNum = port.portA);

			port.portUsed = true;
			Process(nextNum, maxLen + 1, strength + (port.portA + port.portB), ports);

			port.portUsed = false;
		}



	}

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

		temp.portA = first;
		temp.portB = second;
		ports.push_back(temp);

	}

	for (int i = 0; i < ports.size(); ++i)
	{
		if (ports[i].portA == 0 || ports[i].portB == 0)
		{
			zeroPorts.push(ports[i]);
		}
	}


	Process(0, 0, 0, ports);





	std::cout << maxLength << '\n';
	std::cout << maxStrength << '\n';
	std::cout << maxLongestStrength << '\n';
	


	return 0;
}