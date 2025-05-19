#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;


constexpr int PART_1_ITERATIONS = 5;

bool RotateCheck(const string& str, const string& key)
{
	bool result = false;
	string temp = str;
	string tempKey = key;

	temp.erase(remove(temp.begin(), temp.end(), '/'));
	tempKey.erase(remove(tempKey.begin(), tempKey.end(), '/'));
	int rotateTimes = key.size();
	int cntr = 0;

	while (cntr != rotateTimes && result == false)
	{
		rotate(temp.rbegin(), temp.rbegin() + 1, temp.rend());

		if (temp == tempKey)
		{
			result = true;

		}
		else
		{
			++cntr;
		}

	}


	return result;

}

bool FlipCheck(const string& str, const string& key)
{
	string result = str;
	result = { result.rbegin(), result.rend() };

	return (result == key);
}



bool KeyValid(const string& str, const string& key)
{
	string temp = str;
	bool match = false;

	if (temp != key)
	{
		/* flip and check */
		if (FlipCheck(str, key))
		{
			match = true;
		}
		else
		{
			if (RotateCheck(str, key))
			{
				match = true;
			}

			/* do both */
			temp = { temp.rbegin(), temp.rend() };
			if (RotateCheck(temp, key))
			{
				match = true;

			}
		}


	}
	else
	{
		match = true;
	}

	return match;

}

string VecToStr(const vector<string>& vec)
{
	string result;

	for (const string& str : vec)
	{
		result += str + "/";
	}

	result.pop_back();



	return result;
}

vector<string> StrToVec(const string& str)
{
	vector<string> result;
	string temp = str;

	while (temp.find_first_of('/') != string::npos)
	{
		int pos = temp.find_first_of('/');
		result.push_back(temp.substr(0, pos));
		temp.erase(0, pos + 1);
	}

	return result;
}

void HandleDivisible(string& result, const map<string, string>& rules, int div)
{
	/* split to 2x2/3x3 squares */
	vector<string> simulation;
	vector<string> resultVec(10);
	string tempResult = result + "/";
	int currIdx = 0;

	simulation = StrToVec(tempResult);
	int currentStartingRange = 0;

	/* go down vec in increments of div */
	for (int i = 0; i < simulation.size(); i+= div)
	{
		/* go sideways in increments of div */
		for (int j = 0; j < simulation.size(); j += div)
		{
			vector<string> subVec;
			/* get the specified range*/
			for (int k = i; k < i + div; ++k)
			{
				subVec.push_back(simulation[k].substr(currentStartingRange, currentStartingRange + div));

			}


			/* start replacement */
			bool keyFound = false;
			for (auto it = rules.begin(); it != rules.end(); ++it)
			{
				string key = it->first;
				string replacement = it->second + "/";

				string currentToStr = VecToStr(subVec);

				if (KeyValid(key, currentToStr))
				{
					vector<string> keyToVec = StrToVec(replacement);

					int tempIndex = i + 1;
					for (int l = 0; l < keyToVec.size(); ++l)
					{
						if (i == 0)
						{
							resultVec[l].append(keyToVec[l]);
						}
						else
						{
							resultVec[tempIndex].append(keyToVec[l]);
							++tempIndex;

						}

					}
					keyFound = true;
					it = prev(rules.end());
				}

			}


			keyFound = false;


			currentStartingRange += div;
			if (currentStartingRange >= simulation.size() - 1)
			{
				currentStartingRange = 0;
			}



		}




	}
	
	resultVec.erase(remove_if(resultVec.begin(), resultVec.end(), [](const string& str) {return str.empty(); }), resultVec.end());

	result = VecToStr(resultVec);










}


int main()
{
	fstream file; file.open("inputTest.txt");
	map<string, string> rules;
	string line;
	int part1Result = 0;
	string result = ".#./..#/###";


	while (getline(file, line))
	{
		line.erase(remove(line.begin(), line.end(), '='));
		line.erase(remove(line.begin(), line.end(), '>'));
		stringstream stream(line);

		string key, output;

		stream >> key >> output;

		rules[key] = output;

	}


	for (size_t i = 0; i < PART_1_ITERATIONS; ++i)
	{
		int slashCount = count(result.begin(), result.end(), '/');
		if (((result.size() - slashCount) % 2) == 0)
		{
			HandleDivisible(result,rules,2 );
		}
		else if (((result.size() - slashCount) % 3) == 0)
		{
			HandleDivisible(result, rules, 3);
		}



	}

	int cntr = count(result.begin(), result.end(), '#');

	cout << cntr;
	return 0;
}