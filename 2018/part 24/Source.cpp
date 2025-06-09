#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <regex>
#include <sstream>
using namespace std;

enum ArmyType {NONE, IMMUNE,INFECTION};
struct Group
{
	ArmyType type = NONE;
	int units = 0;
	int hp = 0;
	int damage = 0;
	string damageType;
	int initiative = 0;
	set<string> weaknesses;
	set<string> immune;
	Group* selectedTarget = nullptr;

};

void SelectTarget(vector<Group>& groups)
{
	set<int> selectedIndices;
	vector<pair<Group*, int>> sortedGroups;

	for (auto& group : groups)
	{
		if (group.units <= 0) continue;
		int effectivePower = group.units * group.damage;
		sortedGroups.emplace_back(&group, effectivePower);
	}

	// sort groups by effective power, then initiative (descending)
	sort(sortedGroups.begin(), sortedGroups.end(), [](const auto& a, const auto& b)
		{
			if (a.second != b.second) return a.second > b.second;

			return a.first->initiative > b.first->initiative;
		});


	for (auto& attackerPair : sortedGroups)
	{
		Group* attacker = attackerPair.first;

		Group* bestTarget = nullptr;
		int bestDamage = 0;
		int bestTargetPower = 0;
		int bestInitiative = 0;

		for (size_t i = 0; i < groups.size(); ++i)
		{
			Group& target = groups[i];

			// must be opposite army, alive, not immune and not targeted yet
			if (target.type == attacker->type || target.units <= 0 || selectedIndices.count(i)) continue;
			if (target.immune.count(attacker->damageType)) continue;

			// calculate potential dmg
			int damage = attackerPair.second;
			// double dmg if the target is weak to current dmg type
			if (target.weaknesses.count(attacker->damageType))
			{
				damage *= 2;
			}

			if (damage == 0) continue;

			// Prefer max damage, then target power, then initiative
			int targetPower = target.units * target.damage;
			if (damage > bestDamage ||
				(damage == bestDamage && targetPower > bestTargetPower) ||
				(damage == bestDamage && targetPower == bestTargetPower && target.initiative > bestInitiative))
			{
				bestDamage = damage;
				bestTarget = &target;
				bestTargetPower = targetPower;
				bestInitiative = target.initiative;
			}
		}

		if (bestTarget)
		{
			attacker->selectedTarget = bestTarget;
			selectedIndices.insert(distance(groups.begin(), find_if(groups.begin(), groups.end(),
				[bestTarget](const Group& g) { return &g == bestTarget; })));
		}


	}


}

bool Attack(vector<Group>& groups)
{
	bool anyUnitsKilled = false;

	vector<Group*> sorted;

	for (auto& g : groups) 
	{
		if (g.units > 0)
			sorted.push_back(&g);

	}
	// sort by descending initiative
	sort(sorted.begin(), sorted.end(), [](Group* a, Group* b)
		{
			return a->initiative > b->initiative;
		});

	for (Group* attacker : sorted)
	{
		Group* target = attacker->selectedTarget;
		if (!target || attacker->units <= 0 || target->units <= 0) continue;

		int effectivePower = attacker->units * attacker->damage;
		int damage = effectivePower;

		if (target->immune.count(attacker->damageType)) {
			damage = 0;
		}
		else if (target->weaknesses.count(attacker->damageType)) {
			damage *= 2;
		}

		int killed = damage / target->hp;
		killed = min(killed, target->units);

		if (killed > 0)
		{
			target->units -= killed;
			anyUnitsKilled = true;
		}
	}





	return anyUnitsKilled;
}

void ParseWeaknessOrImmunity(const string& section, set<string>& type)
{
	size_t weakPos = section.find("to ") + 3;
	string weakSub = section.substr(weakPos);

	replace(weakSub.begin(), weakSub.end(), ',', ' ');

	stringstream ss(weakSub);
	string word;

	while (ss >> word)
	{
		type.insert(word);
	}
}

int main()
{
	fstream file("input.txt");
	string line;
	vector<Group> groups;
	vector<Group> groupsCopy;
	regex numberRegex(R"((\d+))");
	ArmyType currType = NONE;
	int boost = 1;

	// parse data
	while (getline(file, line))
	{
		Group tempGrp;
		if (line.empty()) continue;
		if (line == "Immune System:")
		{
			currType = IMMUNE;
			continue;
		}
		if (line == "Infection:")
		{
			currType = INFECTION;
			continue;
		}

		// extract nums
		sregex_iterator numbers_begin = sregex_iterator(line.begin(), line.end(), numberRegex);
		sregex_iterator end;
		vector<int> nums;
		for (auto it = numbers_begin; it != end; ++it) 
		{
			nums.push_back(stoi(it->str()));
		}
		tempGrp.type = currType;
		tempGrp.units = nums[0];
		tempGrp.hp = nums[1];
		tempGrp.damage = nums[2];
		tempGrp.initiative = nums[3];

		// get damage type
		size_t dmgPos = line.find("damage");
		if (dmgPos != string::npos)
		{
			stringstream ss(line.substr(0, dmgPos));
			string word;
			while (ss >> word)
			{
				tempGrp.damageType = word;
			}
		}

		// immunity and weakness
		string section = line.substr(line.find('(') + 1, line.find(')') - (line.find('(') + 1));

		// only one weakness/immunity, find it
		if (section.find(';') == string::npos)
		{
			if (section.find("weak") != string::npos)
			{
				ParseWeaknessOrImmunity(section, tempGrp.weaknesses);


			}
			else if (section.find("immune") != string::npos)
			{
				ParseWeaknessOrImmunity(section, tempGrp.immune);
			}


		}
		else
		{
			string firstSection = section.substr(0, section.find(';'));
			string secondSection = section.substr(section.find(';') + 2);

			if (firstSection.find("immune") != string::npos)
			{
				ParseWeaknessOrImmunity(firstSection, tempGrp.immune);
			}
			else
			{
				ParseWeaknessOrImmunity(firstSection, tempGrp.weaknesses);
			}

			if (secondSection.find("immune") != string::npos)
			{
				ParseWeaknessOrImmunity(secondSection, tempGrp.immune);
			}
			else
			{
				ParseWeaknessOrImmunity(secondSection, tempGrp.weaknesses);
			}

		}

		groups.push_back(tempGrp);






	}

	groupsCopy = groups;

	for (Group& g : groups)
	{
		if (g.type == IMMUNE)
		{
			g.damage += boost;
		}
	}

	while (true)
	{
		// reset target
		for (auto& g : groups)
		{
			g.selectedTarget = nullptr;
		}

		// target selection
		SelectTarget(groups);

		// attack target
		bool killed = Attack(groups);

		// check if one side is completely dead
		int immuneAlive = count_if(groups.begin(), groups.end(), [](const Group& g) {
			return g.units > 0 && g.type == IMMUNE;
			});
		int infectionAlive = count_if(groups.begin(), groups.end(), [](const Group& g) {
			return g.units > 0 && g.type == INFECTION;
			});

		//if (immuneAlive == 0 || infectionAlive == 0) 
		//{
		//	cout << "Battle over\n";
		//	break;
		//}


		// part 2

		if (infectionAlive == 0)
		{
			break;
		}
		else if (immuneAlive == 0 || !killed)
		{
			++boost;
			groups = groupsCopy;

			for (Group& g : groups)
			{
				if (g.type == IMMUNE)
				{
					g.damage += boost;
				}
			}
		}

	}


	// part 1
	int totalUnits = 0;
	for (auto& g : groups)
	{
		if (g.units > 0)
			totalUnits += g.units;
	}
	cout << totalUnits;



	return 0;
}