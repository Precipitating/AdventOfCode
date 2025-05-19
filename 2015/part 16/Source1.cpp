#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <array>
#include <regex>
#include <map>

using namespace std;



struct Data
{
	Data() : children(-1), cats(-1), goldfish(-1), trees(-1), cars(-1), perfume(-1), sueNumber(0) {};
	Data(int t_children, int t_cats, int t_goldfish, int t_trees, int t_cars, int t_perfume)
		: children(t_children), cats(t_cats), goldfish(t_goldfish), trees(t_trees), cars(t_cars), perfume(t_perfume), sueNumber(0) {};

	int equalityCount(const Data& rhs)
	{

		auto iter1 = rhs.dogs.find("samoyeds");
		auto iter2 = rhs.dogs.find("pomeranians");
		auto iter3 = rhs.dogs.find("akitas");
		auto iter4 = rhs.dogs.find("vizslas");

		int cntr = 0;
		if (this->children == rhs.children)
		{
			++cntr;
		}
		if (rhs.cats > this->cats)
		{
			++cntr;
		}
		if (rhs.goldfish < this->goldfish)
		{
			++cntr;
		}
		if (rhs.trees > this->trees)
		{
			++cntr;
		}
		if (this->cars == rhs.cars)
		{
			++cntr;
		}
		if (this->perfume == rhs.perfume)
		{
			++cntr;
		}

		if (iter1 != rhs.dogs.end())
		{
			if (iter1->second == 2)
			{
				++cntr;
			}


		}
		if (iter2 != rhs.dogs.end())
		{
			if (iter2->second < 3)
			{
				++cntr;
			}

		}
		if (iter3 != rhs.dogs.end())
		{
			if (iter3->second == 0)
			{
				++cntr;
			}

		}
		if (iter4 != rhs.dogs.end())
		{
			if (iter4->second == 0)
			{
				++cntr;
			}

		}


		return cntr;
	}

	int sueNumber;
	int children;
	int cats;
	map<string, int> dogs;
	int goldfish;
	int trees;
	int cars;
	int perfume;


};


int main()
{
	fstream file;
	string line;
	regex removeFluff("Sue|,|:");
	regex removeSueNumber("//d+");
	file.open("input.txt");
	array<string, 4> dogBreeds = { "samoyeds", "pomeranians", "akitas", "vizslas" };
	int currentSue = 1;
	vector<Data> auntList;


	while (getline(file, line))
	{
		Data tempData;
		string currentData;
		line.erase(line.begin() + 4);
		line = regex_replace(line, removeFluff, "");
		stringstream stream(line);

		tempData.sueNumber = currentSue;

		while (stream >> currentData)
		{
			for (const string& dog : dogBreeds)
			{
				if (currentData.find(dog) != string::npos)
				{
					int tempDigit = 0;
					stream.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
					stream >> tempDigit;

					tempData.dogs.insert(make_pair(dog, tempDigit));

				}

			}
			if (currentData.find("children") != string::npos)
			{
				stream.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
				stream >> tempData.children;
			}
			else if (currentData.find("cats") != string::npos)
			{
				stream.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
				stream >> tempData.cats;
			}
			else if (currentData.find("goldfish") != string::npos)
			{
				stream.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
				stream >> tempData.goldfish;
			}
			else if (currentData.find("trees") != string::npos)
			{
				stream.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
				stream >> tempData.trees;
			}
			else if (currentData.find("cars") != string::npos)
			{
				stream.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
				stream >> tempData.cars;
			}
			else if (currentData.find("perfume") != string::npos)
			{
				stream.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
				stream >> tempData.perfume;
			}



		}

		++currentSue;


		auntList.push_back(tempData);

	}



	/* the most likely aunt is the last element of this vector, as there is more identical hits to the target*/
	vector<Data> possibleAunts;


	Data targetData(3, 7, 5, 3, 2, 1);
	targetData.dogs.insert(make_pair("samoyeds", 2));
	targetData.dogs.insert(make_pair("pomeranians", 3));
	targetData.dogs.insert(make_pair("akitas", 0));
	targetData.dogs.insert(make_pair("vizslas", 0));

	int hitCount = 0;
	//for (int i = 0; i < auntList.size(); ++i)
	//{
	//	int currentHitCount = 0;
	//	auto& x = auntList[i];
	//	currentHitCount = targetData.equalityCount(x);
	//	if (currentHitCount >= 3)
	//	{
	//		hitCount = currentHitCount;
	//		possibleAunts.push_back(x);
	//	}
	//}

	auto condition = [](const Data &elem)
		{
			return (elem.cars != 2 && elem.cars != -1) || (elem.children != 3 &&
					elem.children != -1) || (elem.cats < 7 && elem.cats != -1)||
					(elem.goldfish > 5 && elem.goldfish != -1) || (elem.trees < 3 && elem.trees != -1) ||
					(elem.perfume != 1 && elem.perfume != -1);
		};

	auntList.erase(std::remove_if(auntList.begin(), auntList.end(), condition), auntList.end());

	auto condition2 = [](const Data& elem)
		{

			bool result = true;
			auto iter1 = elem.dogs.find("samoyeds");
			auto iter2 = elem.dogs.find("pomeranians");
			auto iter3 = elem.dogs.find("akitas");
			auto iter4 = elem.dogs.find("vizslas");

			if (iter1 != elem.dogs.end())
			{
				if (iter1->second == 2)
				{
					result = false;
				}
				else
				{
					result = true;
				}


			}
			if (iter2 != elem.dogs.end())
			{
				if (iter2->second < 3)
				{
					result = false;
				}
				else
				{
					result = true;
				}


			}
			if (iter3 != elem.dogs.end())
			{
				if (iter3->second == 0)
				{
					result = false;
				}
				else
				{
					result = true;
				}

			}
			if (iter4 != elem.dogs.end())
			{
				if (iter4->second == 0)
				{
					result = false;
				}
				else
				{
					result = true;
				}

			}

			if (elem.dogs.size() == 0)
			{
				result = false;
			}

			return result;
		};

	auntList.erase(std::remove_if(auntList.begin(), auntList.end(), condition2), auntList.end());
	// 323 answer

	return 0;
}