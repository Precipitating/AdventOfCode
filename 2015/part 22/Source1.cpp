#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <random>
#include <set>
using namespace std;

struct Spell;

enum Winner
{
	NONE,
	PLAYER,
	BOSS
};
struct Stats
{
	Stats(int hp_, int dmg_, int armor_, int mana_) : hp(hp_), damage(dmg_), armor(armor_), mana(mana_) {};

	int hp = 0;
	int damage = 0;
	int armor = 0;
	int mana = 0;

	vector<Spell> effect;

};

struct Spell
{

	bool operator<(const Spell& other) const
	{
		return damage < other.damage;
	}

	string name;
	int damage = 0;
	int cost = 0;
	int heal = 0;
	int armor = 0;
	int turnsItPersists = 0;
	int manaRecharge = 0;
	bool isAllowedToBeUsed = true;
	bool isReoccuring = false;

};

Winner Simulate(Stats boss, Stats player, vector<Spell> spells, set<int>& manaCount)
{
	int totalCost = 0;
	Winner result = NONE;

	int turn = PLAYER;


	while (result == NONE)
	{
		/* determine if anyones dead yet */
		if (boss.hp <= 0)
		{
			result = PLAYER;
			break;
		}
		else if (player.hp <= 0 || player.mana <= 0)
		{
			result = BOSS;
			break;
		}

		if (turn == PLAYER)
		{
			/* part 2 code ---- */
			player.hp -= 1;

			if (player.hp <= 0)
			{
				result = BOSS;
				break;
			}
			/* part 2 code ---- */



			/* apply effect */
			for (auto it = boss.effect.begin(), end = boss.effect.end(); it != end; ++it)
			{

				if (it->isReoccuring && it->turnsItPersists > 0)
				{
					boss.hp -= it->damage;
					if (it->armor > 0)
					{
						player.armor = it->armor;
					}
					player.mana += it->manaRecharge;
					player.hp += it->heal;


					it->turnsItPersists -= 1;

					if (it->turnsItPersists <= 0)
					{
						auto disabledSpell = find_if(spells.begin(), spells.end(), [it](const Spell& current) {return (current.name == it->name); });
						disabledSpell->isAllowedToBeUsed = true;

						if (it->armor > 0)
						{
							player.armor = 0;
						}
					}

				}

			}
			boss.effect.erase(remove_if(boss.effect.begin(), boss.effect.end(), [](const Spell& spell) {return (spell.isReoccuring && spell.turnsItPersists <= 0); }), boss.effect.end());

			/* choose a spell we can use (not ones that the boss has inflicted onto him) */
			std::shuffle(spells.begin(), spells.end(), std::default_random_engine(std::random_device()()));


			while (!spells[0].isAllowedToBeUsed)
			{
				std::shuffle(spells.begin(), spells.end(), std::default_random_engine(std::random_device()()));

			}

			/* ensure we can afford it */

			

			bool affordable = false;


			if (player.mana - spells[0].cost < 0)
			{
				int cnt = 0;
				/* check if NONE of spells are affordable*/
				for (const auto& elem : spells)
				{

					if ((player.mana - elem.cost) < 0 )
					{
						++cnt;
					}

				}

				if (cnt == spells.size())
				{
					result = BOSS;
					affordable = false;
				}
				else
				{
					for (int i = 0; i < spells.size(); ++i)
					{
						if ((player.mana - spells[i].cost >= 0) && spells[i].isAllowedToBeUsed)
						{
							affordable = true;
							iter_swap(spells.begin(), spells.begin() + i);
							break;
						}
					}
				}

			}
			else
			{
				affordable = true;
			}
			if (!affordable)
			{
				break;
			}

			player.mana -= spells[0].cost;
			totalCost += spells[0].cost;



			/* cast spell  */
			/* if its a lasting effect spell ...*/
			if (spells[0].isReoccuring)
			{
				spells[0].isAllowedToBeUsed = false;
			}

			boss.effect.push_back(spells[0]);

			/* handle simple spells drain and magic missile */
			if (!spells[0].isReoccuring)
			{
				boss.hp -= spells[0].damage;
				player.hp += spells[0].heal;
				boss.effect.erase(remove_if(boss.effect.begin(), boss.effect.end(), [](const Spell& spell) {return (!spell.isReoccuring && spell.turnsItPersists <= 0); }), boss.effect.end());

			}


			if (boss.hp <= 0)
			{
				result = PLAYER;
				break;
			}
			turn = BOSS;
		}
		else if (turn == BOSS)
		{
			if (player.mana > 0)
			{
				/* handle effects */
				if (boss.effect.size() > 0)
				{
					for (auto it = boss.effect.begin(), end = boss.effect.end(); it != end; ++it)
					{

						if (it->isReoccuring && it->turnsItPersists > 0)
						{
							boss.hp -= it->damage;
							if (it->armor > 0)
							{
								player.armor = it->armor;

							}
							player.mana += it->manaRecharge;
							player.hp += it->heal;


							it->turnsItPersists -= 1;

							if (it->turnsItPersists <= 0)
							{
								auto disabledSpell = find_if(spells.begin(), spells.end(), [it](const Spell& current) {return (current.name == it->name); });
								disabledSpell->isAllowedToBeUsed = true;
								if (it->armor > 0)
								{
									player.armor = 0;
								}
							}

						}

					}
					boss.effect.erase(remove_if(boss.effect.begin(), boss.effect.end(), [](const Spell& spell) {return (spell.isReoccuring && spell.turnsItPersists <= 0); }), boss.effect.end());



				}


			}

			if (boss.hp <= 0)
			{
				result = PLAYER;
				break;
			}
			/* boss attack*/
			player.hp -= (boss.damage - player.armor);

			turn = PLAYER;
		}







	}
	if (result == PLAYER)
	{
		manaCount.insert(totalCost);
	}


	return result;

}
int main()
{
	fstream file;
	file.open("spells.txt");
	string line;
	Stats boss(58, 9, 0, 0);
	Stats player(50, 0, 0, 500);
	vector<Spell> spells;
	set<int> manaCount;


	while (getline(file, line))
	{
		stringstream stream(line);
		Spell currentSpell;

		stream >> currentSpell.name >> currentSpell.cost >> currentSpell.damage >>
			currentSpell.heal >> currentSpell.armor >> currentSpell.turnsItPersists >>
			currentSpell.manaRecharge;

		if (currentSpell.turnsItPersists > 0)
		{
			currentSpell.isReoccuring = true;
		}
		spells.push_back(currentSpell);


	}



	while (manaCount.size() < 9999)
	{
		Simulate(boss, player, spells, manaCount);
	}










	return 0;


}