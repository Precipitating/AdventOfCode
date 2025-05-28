#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

enum class DIRECTION
{
	NONE,
	UP,
	DOWN,
	LEFT,
	RIGHT
};

enum class DIRECTION_ORDER: int
{
	LEFT = 0,
	STRAIGHT = 1,
	RIGHT = 2
};

struct Cart
{
	DIRECTION dir = DIRECTION::NONE;
	DIRECTION_ORDER dirOrder = DIRECTION_ORDER::LEFT;
	int x = 0;
	int y = 0;
	bool removed = false;

	void Set(int x_, int y_, DIRECTION dir_)
	{
		x = x_;
		y = y_;
		dir = dir_;
	}
	bool operator==(const Cart& other) const
	{
		return (other.x == x) && (other.y == y);
	}

	void Move(const vector<string>& track)
	{

		// execute one step
		switch (dir)
		{
		case DIRECTION::UP: --x; break;
		case DIRECTION::DOWN: ++x; break;
		case DIRECTION::LEFT: --y; break;
		case DIRECTION::RIGHT: ++y; break;

		}


		// handle next movement
		switch (track[x][y])
		{
		case '+':
		{
			switch (dirOrder)
			{
			case DIRECTION_ORDER::LEFT:
			{
				switch (dir)
				{
				case DIRECTION::LEFT:	dir = DIRECTION::DOWN; break;
				case DIRECTION::RIGHT:	dir = DIRECTION::UP; break;
				case DIRECTION::UP:		dir = DIRECTION::LEFT; break;
				case DIRECTION::DOWN:	dir = DIRECTION::RIGHT; break;
				}
				break;
			}

			case DIRECTION_ORDER::RIGHT:
			{
				switch (dir)
				{
				case DIRECTION::LEFT:	dir = DIRECTION::UP; break;
				case DIRECTION::RIGHT:	dir = DIRECTION::DOWN; break;
				case DIRECTION::UP:		dir = DIRECTION::RIGHT; break;
				case DIRECTION::DOWN:	dir = DIRECTION::LEFT; break;
				}
				break;
			}
			}

			dirOrder = static_cast<DIRECTION_ORDER>((static_cast<int>(dirOrder) + 1) % 3);
			break;
		}
		case '/':
		{
			switch (dir)
			{
			case DIRECTION::LEFT:	dir = DIRECTION::DOWN; break;
			case DIRECTION::RIGHT:	dir = DIRECTION::UP; break;
			case DIRECTION::UP:		dir = DIRECTION::RIGHT; break;
			case DIRECTION::DOWN:	dir = DIRECTION::LEFT; break;
			}
			break;
		}
		case '\\':
		{
			switch (dir)
			{
			case DIRECTION::LEFT:	dir = DIRECTION::UP; break;
			case DIRECTION::RIGHT:	dir = DIRECTION::DOWN; break;
			case DIRECTION::UP:		dir = DIRECTION::LEFT; break;
			case DIRECTION::DOWN:	dir = DIRECTION::RIGHT; break;
			}
			break;
		}

		}


	}

};


bool Crashed(const std::vector<Cart>& cartLocs, std::pair<int, int>& loc)
{
	set<pair<int, int>> seen;

	for (const auto& cart : cartLocs)
	{
		pair<int, int> pos = { cart.x, cart.y };
		if (seen.count(pos))
		{
			loc = pos;
			return true;

			// par
		}
		seen.insert(pos);
	}

	return false;
}

bool CrashedRemove(int i, vector<Cart>& cartLocs)
{
	bool isRemoved = false;
	for (size_t j = 0; j < cartLocs.size(); ++j)
	{
		if (i != j && cartLocs[i] == cartLocs[j])
		{
			auto crashPos = std::make_pair(cartLocs[i].x, cartLocs[i].y);
			cartLocs.erase(
				std::remove_if(cartLocs.begin(), cartLocs.end(),
					[&](const Cart& c) { return c.x == crashPos.first && c.y == crashPos.second; }),
				cartLocs.end()
			);
			isRemoved = true;
		}
	}
	return isRemoved;

}







int main()
{
	fstream file("input.txt");
	string line;
	vector<string> track;
	vector<Cart> cartLocations;
	pair<int, int> result;

	while (getline(file, line))
	{
		track.push_back(line);
	}

	// get cart locations
	for (size_t i = 0; i < track.size(); ++i)
	{
		Cart cart;
		for (size_t j = 0; j < track[i].size(); ++j)
		{
			switch (track[i][j])
			{
			case '^': cart.Set(i, j, DIRECTION::UP);	 cartLocations.push_back(cart); break;
			case 'v': cart.Set(i, j, DIRECTION::DOWN);	 cartLocations.push_back(cart); break;
			case '<': cart.Set(i, j, DIRECTION::LEFT);	 cartLocations.push_back(cart); break;
			case '>': cart.Set(i, j, DIRECTION::RIGHT); cartLocations.push_back(cart); break;
			}
		}
	}

	bool crashed = false;
	

	while (!crashed)
	{
		sort(cartLocations.begin(), cartLocations.end(), [](const Cart& a, const Cart& b) {
			return tie(a.x, a.y) < tie(b.x, b.y);
			});

		for (size_t i = 0; i < cartLocations.size(); ++i)
		{
			cartLocations[i].Move(track);

			// part 1
			//if (Crashed(cartLocations, result))
			//{
			//	crashed = true;
			//	break;
			//}


			// part 2
			for (size_t j = 0; j < cartLocations.size(); ++j)
			{
				if (i == j || cartLocations[j].removed) continue;

				if (cartLocations[i] == cartLocations[j])
				{
					cartLocations[i].removed = true;
					cartLocations[j].removed = true;
					break;
				}
			}
		}

		// Remove all crashed carts after tick
		cartLocations.erase(
			std::remove_if(cartLocations.begin(), cartLocations.end(),
				[](const Cart& c) { return c.removed; }),
			cartLocations.end()
		);


		if (cartLocations.size() == 1)
		{
			result = { cartLocations[0].x, cartLocations[0].y };
			crashed = true;
		}
	}



	cout << result.second << ' ' << result.first;


	return 0;
}