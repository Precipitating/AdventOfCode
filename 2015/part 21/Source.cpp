#include <iostream>
#include <regex>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;


enum Winner
{
	NONE,
	BOSS,
	PLAYER

};
enum Category
{
	WEAPON,
	ARMOR,
	RINGS
};

struct ShopValues
{

	bool operator < (const ShopValues& str) const
	{
		return (cost < str.cost);
	}

	Category itemType;
	string name;
	int cost = 0;
	int damage = 0;
	int armor = 0;


};

struct Stats
{
	int hp = 0;
	int dmg = 0;
	int armor = 0;
};



Winner Simulate(Stats boss, Stats player)
{
	bool turn = false;
	Winner winner = NONE;
	do
	{
		if (player.hp <= 0)
		{
			winner = BOSS;
		}
		else if (boss.hp <= 0)
		{
			winner = PLAYER;
		}
		/* player attack*/
		if (!turn)
		{
			boss.hp -= (player.dmg - boss.armor);
			turn = !turn;
		}
		/* boss attack*/
		else
		{
			player.hp -= (boss.dmg - player.armor);
			turn = !turn;
		}



	} while (winner == NONE);

	return winner;

}


int main()
{
	Stats player;
	player.hp = 100;
	Stats boss;
	fstream file;
	string line;
	file.open("input.txt");
	vector<vector<ShopValues>> shop;
	regex colonRemove(":|Hit Points|Damage|Armor");
	vector<int> WinCost;

	int count = 0;
	while (getline(file, line))
	{
		line = regex_replace(line, colonRemove, "");

		stringstream stream(line);


		switch (count)
		{
		case 0:
			stream >> boss.hp;
			break;
		case 1: 
			stream >> boss.dmg;
			break;
		case 2:
			stream >> boss.armor;
		}

		++count;

	}
	file.close();
	file.open("shop.txt");

	count = 0;
	vector<ShopValues> tempVec;
	while (getline(file, line))
	{
		ShopValues tempVals;
		stringstream stream(line);

		if (line.empty())
		{
			++count;
			shop.push_back(tempVec);
			tempVec.clear();

		}
		else
		{
			switch (count)
			{
			case 0:
				tempVals.itemType = WEAPON;
				stream >> tempVals.name >> tempVals.cost >> tempVals.damage >> tempVals.armor;
				tempVec.push_back(tempVals);
				break;
			case 1:
				tempVals.itemType = ARMOR;
				stream >> tempVals.name >> tempVals.cost >> tempVals.damage >> tempVals.armor;
				tempVec.push_back(tempVals);
				break;
			case 2:
				tempVals.itemType = RINGS;
				stream >> tempVals.name >> tempVals.cost >> tempVals.damage >> tempVals.armor;
				tempVec.push_back(tempVals);
				break;
			}
		}

		if (file.eof())
		{
			shop.push_back(tempVec);
		}






	}

	/* conditions: one weapon, optional armor, 0-2 rings can be chosen */

	/* only weapons section:*/
	sort(shop[WEAPON].begin(), shop[WEAPON].end());
	for (int i = 0; i < shop[WEAPON].size(); ++i)
	{
		Stats boostedPlayer = player;
		boostedPlayer.dmg += shop[WEAPON][i].damage;
		boostedPlayer.armor += shop[WEAPON][i].armor;


		int goldSpent = shop[WEAPON][i].cost;

		if (Simulate(boss, boostedPlayer) == BOSS)
		{
			WinCost.push_back(goldSpent);
		};
	}

	/* weapon and armor*/
	for (int i = 0; i < shop[WEAPON].size(); ++i)
	{
		Stats boostedPlayer = player;

		/* weapon add */
		boostedPlayer.dmg = shop[WEAPON][i].damage;
		boostedPlayer.armor = shop[WEAPON][i].armor;
		int goldSpent = shop[WEAPON][i].cost;

		for (int j = 0; j < shop[ARMOR].size(); ++j)
		{
			/* rest values per loop*/
			goldSpent = shop[WEAPON][i].cost;
			boostedPlayer.armor = shop[WEAPON][i].armor;
			boostedPlayer.dmg = shop[WEAPON][i].damage;

			boostedPlayer.armor += shop[ARMOR][j].armor;
			goldSpent += shop[ARMOR][j].cost;

			if (Simulate(boss, boostedPlayer) == BOSS)
			{
				WinCost.push_back(goldSpent);
			};

		}




	}


	/* weapon and armor and 1 ring*/
	for (int i = 0; i < shop[WEAPON].size(); ++i)
	{
		Stats boostedPlayer = player;

		/* weapon add */
		boostedPlayer.dmg = shop[WEAPON][i].damage;
		boostedPlayer.armor = shop[WEAPON][i].armor;
		int goldSpent = shop[WEAPON][i].cost;

		for (int j = 0; j < shop[ARMOR].size(); ++j)
		{
			/* rest values per loop*/
			goldSpent = shop[WEAPON][i].cost;
			boostedPlayer.armor = shop[WEAPON][i].armor;

			boostedPlayer.armor += shop[ARMOR][j].armor;
			goldSpent += shop[ARMOR][j].cost;

			for (int k = 0; k < shop[RINGS].size(); ++k)
			{
				/* rest values per loop*/
				goldSpent = shop[WEAPON][i].cost + shop[ARMOR][j].cost;
				boostedPlayer.armor = shop[WEAPON][i].armor + shop[ARMOR][j].armor;
				boostedPlayer.dmg = shop[WEAPON][i].damage + shop[ARMOR][j].damage;

				goldSpent += shop[RINGS][k].cost;
				boostedPlayer.armor += shop[RINGS][k].armor;
				boostedPlayer.dmg += shop[RINGS][k].damage;


				if (Simulate(boss, boostedPlayer) == BOSS)
				{
					WinCost.push_back(goldSpent);
				};

			}


		}




	}

	/* weapon and armor and 2 ring*/
	for (int i = 0; i < shop[WEAPON].size(); ++i)
	{
		Stats boostedPlayer = player;

		/* weapon add */
		boostedPlayer.dmg = shop[WEAPON][i].damage;
		boostedPlayer.armor = shop[WEAPON][i].armor;
		int goldSpent = shop[WEAPON][i].cost;

		for (int j = 0; j < shop[ARMOR].size(); ++j)
		{
			/* rest values per loop*/
			goldSpent = shop[WEAPON][i].cost;
			boostedPlayer.armor = shop[WEAPON][i].armor;

			boostedPlayer.armor += shop[ARMOR][j].armor;
			goldSpent += shop[ARMOR][j].cost;

			for (int k = 0; k < shop[RINGS].size() - 1; ++k)
			{
				/* rest values per loop*/
				goldSpent = shop[WEAPON][i].cost + shop[ARMOR][j].cost;
				boostedPlayer.armor = shop[WEAPON][i].armor + shop[ARMOR][j].armor;
				boostedPlayer.dmg = shop[WEAPON][i].damage + shop[ARMOR][j].damage;

				goldSpent += shop[RINGS][k].cost;
				boostedPlayer.armor += shop[RINGS][k].armor;
				boostedPlayer.dmg += shop[RINGS][k].damage;

				for (int l = k + 1 ; l < shop[RINGS].size(); ++l)
				{

					/* rest values per loop*/
					goldSpent = shop[WEAPON][i].cost + shop[ARMOR][j].cost + shop[RINGS][k].cost;
					boostedPlayer.armor = shop[WEAPON][i].armor + shop[ARMOR][j].armor + shop[RINGS][k].armor;
					boostedPlayer.dmg = shop[WEAPON][i].damage + shop[ARMOR][j].damage + shop[RINGS][k].damage;

					goldSpent += shop[RINGS][l].cost;
					boostedPlayer.armor += shop[RINGS][l].armor;
					boostedPlayer.dmg += shop[RINGS][l].damage;



					if (Simulate(boss, boostedPlayer) == BOSS)
					{
						WinCost.push_back(goldSpent);
					};

				}


			}


		}




	}
	sort(WinCost.begin(), WinCost.end());
	return 0;

}