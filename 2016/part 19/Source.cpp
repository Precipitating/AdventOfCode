#include <iostream>
#include <vector>
#include <list>

const int INPUT = 3004953;
const int INPUT2 = 10;

struct Elf
{
	int idx = 1;
	int presentCount = 1;
};

int main()
{
	std::list<Elf> elves(INPUT);
	int idx = 1;
	std::list<Elf>::iterator currentIdx = elves.begin();
	
	for (auto it = elves.begin(); it != elves.end(); ++it)
	{
		it->idx = idx;
		++idx;

	}


	while (elves.size() != 1)
	{

		if (currentIdx == std::prev(elves.end()))
		{
			currentIdx->presentCount += elves.front().presentCount;
			elves.front().presentCount = 0;
			currentIdx = elves.begin();
			currentIdx = elves.erase(currentIdx);
		}
		else
		{
			currentIdx->presentCount += std::next(currentIdx)->presentCount;
			std::next(currentIdx)->presentCount = 0;
			currentIdx = elves.erase(std::next(currentIdx));

			if (currentIdx == elves.end())
			{
				currentIdx = elves.begin();
			}

		}


	}

	std::cout << elves.front().idx;

	return 0;
}