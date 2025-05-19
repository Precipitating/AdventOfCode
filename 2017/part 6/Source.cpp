#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>


using namespace std;


int main()
{
	fstream file; file.open("input.txt");
	string line;
	int cycle = 0;
	vector<int> memory;
	bool end = false;
	set<vector<int>> visited;

	while (getline(file, line))
	{
		int mem;
		stringstream stream(line);

		while (stream >> mem)
		{
			memory.push_back(mem);
		}



	}

	visited.insert(memory);
	while (!end)
	{
		/* get largest element in memory */
		int currentLargestElem = *max_element(memory.begin(), memory.end());
		int selectedMemory = 0;

		/* get the first match of largest element from vector */
		for (int i = 0; i < memory.size(); ++i)
		{
			if (memory[i] == currentLargestElem)
			{
				selectedMemory = i;
				memory[i] = 0;
				break;
			}
		}

		int currentIdx = selectedMemory + 1;
		while (currentLargestElem != 0)
		{
			if (currentIdx > (memory.size() - 1))
			{
				currentIdx = 0;
			}

			++memory[currentIdx];
			++currentIdx;
			--currentLargestElem;



		}



		if (visited.insert(memory).second == true)
		{
			visited.insert(memory);
			++cycle;
		}
		else
		{
			++cycle;
			cout << cycle << '\n';
			end = true;
		}


	}





	return 0;
}