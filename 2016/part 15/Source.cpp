#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>
#include <algorithm>

using namespace std;

struct Disc
{

	int discNumber = 0;
	int currentPosition = 0;
	int positions = 0;
	int currentTime = 0;
};

bool CheckTimeAt(int time, vector<Disc> discs)
{
	bool found = false;
	int cntr = 1;
	for (int i = 0; i < discs.size(); ++i)
	{
		int tickAmount = time + cntr;

		if ((discs[i].currentPosition + tickAmount) >= discs[i].positions)
		{
			int offset = (discs[i].currentPosition + tickAmount) - discs[i].positions;
			while (offset >= discs[i].positions)
			{
				offset -= discs[i].positions;
			}


			discs[i].currentPosition = 0;

			discs[i].currentPosition += offset;

		}
		else
		{
			discs[i].currentPosition += tickAmount;
		}
		++cntr;


	}
	int num = discs[0].currentPosition;

	int cnt = count_if(discs.begin(), discs.end(), [num](const Disc& x) {return x.currentPosition == num; });

	if (cnt == discs.size())
	{
		found = true;
	}
	return found;

}

int main()
{
	fstream file; file.open("input.txt");
	string line;
	regex fluffRemover("#|Disc|has|positions|at|time=|,|it|is|at|position|\\.|;");
	regex spaceDupe("\\s+");
	vector<Disc> discs; discs.reserve(6);

	/* parse data into a vector*/
	while (getline(file, line))
	{
		Disc currentDisc;
		line = regex_replace(line, fluffRemover, "");
		line = regex_replace(line, spaceDupe, " ");
		stringstream stream(line);

		stream >> currentDisc.discNumber >> currentDisc.positions >> currentDisc.currentTime >> currentDisc.currentPosition;


		discs.push_back(currentDisc);

	}

	Disc part2Disc;
	part2Disc.discNumber = discs.size() + 1;
	part2Disc.currentPosition = 0;
	part2Disc.positions = 11;
	discs.push_back(part2Disc);



	bool found = false;
	int time = 0;
	while (!found)
	{
		/* if all discs same position, we got it*/

		if (CheckTimeAt(time, discs))
		{
			cout << time << '\n';
			found = true;
		}
		else
		{
			++time;
		}
		





	}



	return 0;
}
