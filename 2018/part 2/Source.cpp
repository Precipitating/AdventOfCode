#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
	fstream file; file.open("input.txt");
	string line;
	int twoTimes = 0;
	int threeTimes = 0;

	while (getline(file, line))
	{
		bool threeFound = false;
		bool twoFound = false;

		
		for (int i = 0; i < line.size(); ++i)
		{

			if (threeFound && twoFound)
			{
				break;
			}


			if (line[i] != '*')
			{
				char cur = line[i];
				int cnt = count(line.begin(), line.end(), cur);


				if (cnt == 2 && !twoFound)
				{
					++twoTimes;
					twoFound = true;
				}

				if (cnt == 3 && !threeFound)
				{
					++threeTimes;
					threeFound = true;
				}

				replace(line.begin(), line.end(), cur, '*');
			}
			

		}

		


	}


	cout << (twoTimes * threeTimes);
	return 0;
}