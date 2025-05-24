#include <iostream>
#include <list>
#include <string>
#include <vector>
using namespace std;


int main()
{
	int lastMarble = 71082;
	int part2Marble = lastMarble * 100;
	int players = 413;
	list<long long> list = { 0 };
	auto currentPos = list.begin();

	vector<long long> currentPlayer(players,0);
	int currPlayer = 0;

	for (size_t i = 0; i < part2Marble; ++i)
	{
		if ((i+1) % 23 == 0)
		{
			currentPlayer[currPlayer] += i + 1;

			for (size_t j = 0; j < 7; ++j)
			{
				if (currentPos == list.begin())
				{
					currentPos = prev(list.end());
				}
				else
				{
					--currentPos;
				}

			}
			currentPlayer[currPlayer] += *currentPos;
			currentPos = list.erase(currentPos);

		}
		else
		{
			auto insertPos = std::next(currentPos);
			if (insertPos == list.end())
			{
				insertPos = list.begin();
			}


			insertPos = std::next(insertPos);
			if (insertPos == list.end())
			{
				insertPos = list.begin();
			}

			currentPos = list.insert(insertPos, i + 1);


		}

		currPlayer = (currPlayer + 1) % players;

	}

	std::cout << *max_element(currentPlayer.begin(), currentPlayer.end()) << '\n';







	return 0;
}