#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <vector>
using namespace std;


int main()
{
	fstream file; file.open("input.txt");
	string line;
	int part1 = 0;
	int part2 = -1;
	set<int> dupes;
	vector<int> loop;

	dupes.insert(part1);

	while (getline(file, line))
	{
		stringstream stream(line);
		int num;

		stream >> num;
		loop.push_back(num);
		part1 += num;


		dupes.insert(part1);





	}


	while (part2 == -1)
	{
		for (const int& num : loop)
		{
			part1 += num;

			if (dupes.count(part1) == 0)
			{
				dupes.insert(part1);
			}
			else
			{
				part2 = part1;
				cout << part2 << '\n';
				break;
			}



		}


	}


	return 0;

}