#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include "Header.h"
using namespace std;

struct Package
{
	vector<int> combo;
	double product;

	int CalculateProduct() const
	{
		int prod = 0;

		for (int i = 0; i < combo.size() - 1; ++i)
		{
			prod = combo[i] * combo[i + 1];
		}

		return prod;
	}


};


bool FindLowestPossibleSet(int range, vector<int>& vec, const int& target)
{
	bool result = false;
	vector<Package> lowVec;
	Package temp;
	vector<int>& correctCombo = temp.combo;

	typedef std::vector<int>::iterator Iter;
	for_each_combination(vec.begin(), vec.begin() + range, vec.end(),
		[&](Iter f, Iter l)
		{
			vector<int> sum;
			for (; f != l; ++f)
				sum.push_back(*f);
				

			if ((accumulate(sum.begin(), sum.end(), 0) == target))
			{

				correctCombo = sum;
				temp.product = std::accumulate(sum.begin(), sum.end(), 1.0, std::multiplies<double>());
				lowVec.push_back(temp);
			}

			temp.combo.clear();

			return false;
		}
	);

	sort(lowVec.begin(), lowVec.end(), [](const Package& thiz, const Package& other) {return thiz.product < other.product; });
	return result;
}

int main()
{
	fstream file;
	file.open("input.txt");
	vector<int> numberList;
	string line;


	while (getline(file, line))
	{

		numberList.push_back(stoi(line));

	}


	int weight = accumulate(numberList.begin(), numberList.end(),0 ) / 4;


	int i = 4;

	FindLowestPossibleSet(4, numberList, weight);

	cout << i;

	return 0;
}