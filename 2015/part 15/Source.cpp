#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <regex>
#include <vector>
#include <algorithm>
#include "Header.h"

using namespace std;
struct Ingredient
{
	string name;
	int capacity;
	int durability;
	int flavour;
	int texture;
	int calories;


};

int HandleCombination(const vector<Ingredient>& combo)
{
	int score = 0;
	int capacity;
	int durability;
	int flavour;
	int texture;
	int calories;

	for (int i = 1; i < 99; ++i)
	{
		capacity = (i * combo[0].capacity) + ((100 - i) * combo[1].capacity);
		durability = (i * combo[0].durability) + ((100 - i) * combo[1].durability);
		flavour = (i * combo[0].flavour) + ((100 - i) * combo[1].flavour);
		texture = (i * combo[0].texture) + ((100 - i) * combo[1].texture);
		calories = (i * combo[0].calories)+ ((100 - i ) * combo[1].calories);

		capacity = std::max(0, capacity);
		durability = std::max(0, durability);
		flavour = std::max(0, flavour);
		texture = std::max(0, texture);


		if ((capacity * durability * flavour * texture) > score && calories == 500)
		{
			score = capacity * durability * flavour * texture;
		}

	}

	return score;
}


int HandleCombination2(const vector<Ingredient>& combo)
{
	int score = 0;
	int capacity;
	int durability;
	int flavour;
	int texture;
	int calories;

	for (int i = 1; i < 98; ++i)
	{
		for (int j = 1; (j + i) < 100; ++j)
		{



			capacity = (i * combo[0].capacity) + (j * combo[1].capacity) + ((100 - i - j) * combo[2].capacity);
			durability = (i * combo[0].durability) + (j * combo[1].durability) + ((100 - i - j) * combo[2].durability);
			flavour = (i * combo[0].flavour) + (j * combo[1].flavour)  +  ((100 - i - j) * combo[2].flavour);
			texture = (i * combo[0].texture) + (j * combo[1].texture) + ((100 - i - j) * combo[2].texture);
			calories = (i * combo[0].calories) + (j * combo[1].calories) + ((100 - i - j) * combo[2].calories);

			capacity = std::max(0, capacity);
			durability = std::max(0, durability);
			flavour = std::max(0, flavour);
			texture = std::max(0, texture);


			if ((capacity * durability * flavour * texture) > score && calories == 500)
			{
				score = capacity * durability * flavour * texture;
			}
		}

	}

	return score;
}

int HandleCombination3(const vector<Ingredient>& combo)
{
	int score = 0;
	int capacity;
	int durability;
	int flavour;
	int texture;
	int calories;

	/* delete calories = 500 requirement to get rid of part 2 answer*/
	for (int i = 1; i <= 100; ++i)
	{
		for (int j = 1; j <= 100 - i; ++j)
		{

			for (int k = 1; k <= 100 - i - j; ++k)
			{
				int test = 100 - i - j - k;

				capacity = (i * combo[0].capacity) + (j * combo[1].capacity)		+ (k * combo[2].capacity) +		((100 - i - j - k) * combo[3].capacity);
				durability = (i * combo[0].durability) + (j * combo[1].durability)	+ (k * combo[2].durability) +	((100 - i - j - k) * combo[3].durability);
				flavour = (i * combo[0].flavour) + (j * combo[1].flavour)			+ (k * combo[2].flavour) +		((100 - i - j - k) * combo[3].flavour);
				texture = (i * combo[0].texture) + (j * combo[1].texture)			+ (k * combo[2].texture) +		((100 - i - j - k) * combo[3].texture);
				calories = (i * combo[0].calories) + (j * combo[1].calories)			+ (k * combo[2].calories) +		((100 - i - j - k) * combo[3].calories);

				capacity = std::max(0, capacity);
				durability = std::max(0, durability);
				flavour = std::max(0, flavour);
				texture = std::max(0, texture);


				if ((capacity * durability * flavour * texture) > score && calories == 500)
				{
					score = capacity * durability * flavour * texture;
				}
			}

			
		}

	}

	return score;
}

int main()
{
	int maxCapacity = 100;
	fstream file;
	string line;
	file.open("input.txt");
	regex extractor(",|:|capacity|durability|flavor|texture|calories");
	vector<Ingredient> ingredients;

	int highestScore = 0;
	
	while (getline(file, line))
	{
		Ingredient temp;
		line = regex_replace(line, extractor, "");
		stringstream stream(line);

		stream >> temp.name >> temp.capacity >> temp.durability >> temp.flavour >> temp.texture >> temp.calories;


		ingredients.push_back(temp);

	}
	typedef std::vector<Ingredient>::iterator Iter;
	for_each_permutation(ingredients.begin(), ingredients.begin() + 2, ingredients.end(),
		[&highestScore](Iter f, Iter l)
		{
			vector<Ingredient> currentCombo;
			for (; f != l; ++f)
				currentCombo.push_back(*f);

			if (HandleCombination(currentCombo) > highestScore)
			{
				highestScore = HandleCombination(currentCombo);
			};
			
			return false;
		}
	);

	for_each_permutation(ingredients.begin(), ingredients.begin() + 3, ingredients.end(),
		[&highestScore](Iter f, Iter l)
		{
			vector<Ingredient> currentCombo;
			for (; f != l; ++f)
				currentCombo.push_back(*f);

			if (HandleCombination2(currentCombo) > highestScore)
			{
				highestScore = HandleCombination2(currentCombo);
			};

			return false;
		}
	);


	for_each_permutation(ingredients.begin(), ingredients.begin() + 4, ingredients.end(),
		[&highestScore](Iter f, Iter l)
		{
			vector<Ingredient> currentCombo;
			for (; f != l; ++f)
				currentCombo.push_back(*f);

			if (HandleCombination3(currentCombo) > highestScore)
			{
				highestScore = HandleCombination3(currentCombo);
			};

			return false;
		}
	);
	std::cout << highestScore;

	
}