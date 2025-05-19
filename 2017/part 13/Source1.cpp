#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;



struct Layer
{
	bool operator<(const Layer& other) const
	{
		return length < other.length; // Example comparison logic
	}

	int currentPos = 0;
	int length = 0;
	bool reversed = false;

	void Reset()
	{
		currentPos = 0;
		reversed = false;
	}
};
void MoveOnce(map<int, Layer>& map)
{
	for (auto it = map.begin(); it != map.end(); ++it)
	{
		Layer& layer = it->second;

		if (layer.length != 0)
		{
			if (!layer.reversed)
			{
				if (layer.currentPos == layer.length)
				{
					layer.reversed = true;
					--layer.currentPos;
				}
				else
				{
					++layer.currentPos;
				}
			}
			else if (layer.reversed)
			{
				if (layer.currentPos == 0)
				{
					layer.reversed = false;
					++layer.currentPos;
				}
				else
				{
					--layer.currentPos;
				}
			}
		}



	}




}

int main()
{
	fstream file; file.open("input.txt");
	int packetPos = 0;
	string line;
	map<int, Layer> layers;
	int severity = -1;

	while (getline(file, line))
	{
		int id = 0; int length = 0;
		line.erase(std::remove(line.begin(), line.end(), ':'), line.end());
		stringstream stream(line);

		stream >> id >> length;

		layers[id].length = length - 1;

	}


	auto maxElem = *max_element(layers.begin(), layers.end());
	int maxNum = maxElem.first;

	for (int i = 0; i < maxNum; ++i)
	{
		if (layers.count(i) != 1)
		{
			layers[i].length = 0;
		}

	}

	int delayTime = 0;
	bool done = false;
	bool caught = false;
	while (!done)
	{

		for (auto it = layers.begin(); it != layers.end(); ++it)
		{
			if (it->second.length != 0)
			{
				if ((delayTime + it->first) % ((it->second.length ) * 2) == 0)
				{
					caught = true;
					break;
				}


			}

		}

		if (!caught)
		{
			cout << delayTime;
			done = true;
		}
		else
		{
			++delayTime;
			caught = false;
		}
	}


	return 0;
}