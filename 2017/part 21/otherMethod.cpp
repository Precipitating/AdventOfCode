#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;


constexpr int PART_1_ITERATIONS = 5;
constexpr int PART_2_ITERATIONS = 18;
string VecToStr(const vector<string>& vec);

string Flip(const string& str)
{
	int pos = 0;
	vector<string> toVec;
	vector<string> invertedVec;
	string tempStr = str;
	string result;

	while (pos != -1)
	{
		if (pos == 0)
		{
			toVec.push_back(tempStr.substr(0, tempStr.find_first_of("/")));

			pos = tempStr.find_first_of("/");
		}
		else
		{
			toVec.push_back(tempStr.substr(pos + 1, tempStr.find_first_of("/", pos)));

			pos = tempStr.find_first_of("/", pos + 1);


		}

	}

	invertedVec = toVec;


	int idx = toVec.size() - 1;


	for (size_t j = 0; j < invertedVec.size(); ++j)
	{
		invertedVec[j] = toVec[idx];
		--idx;
	}




	result = VecToStr(invertedVec);


	return result;
}
string Symmetric(const string& str)
{
	int pos = 0;
	vector<string> toVec;
	vector<string> invertedVec;
	string tempStr = str;
	string result;

	while (pos != -1)
	{
		if (pos == 0)
		{
			toVec.push_back(tempStr.substr(0, tempStr.find_first_of("/")));

			pos = tempStr.find_first_of("/");
		}
		else
		{
			toVec.push_back(tempStr.substr(pos + 1, tempStr.find_first_of("/", pos)));

			pos = tempStr.find_first_of("/", pos + 1 );


		}

	}

	invertedVec = toVec;


	for (int i = 0; i < invertedVec.size(); ++i)
	{
		string& row = toVec[i];

		for (int j = 0; j < row.size(); ++j)
		{
			invertedVec[j][i] = row[j];
		}

	}


	result = VecToStr(invertedVec);


	return result;
}

bool RotateCheck(const string& str, const string& key)
{
	bool result = false;
	string temp = str;
	string tempKey = key;

	//temp.erase(remove(temp.begin(), temp.end(), '/'));
	//tempKey.erase(remove(tempKey.begin(), tempKey.end(), '/'));


	/* -90 deg rot*/
	tempKey = Symmetric(tempKey);
	tempKey = Flip(tempKey); 

	result = (str == tempKey);

	tempKey = Symmetric(tempKey);
	tempKey = Flip(tempKey);

	if (!result) { result = (str == tempKey); }

	tempKey = Symmetric(tempKey);
	tempKey = Flip(tempKey);

	if (!result) { result = (str == tempKey); }

	/* original */
	tempKey = Symmetric(tempKey);
	tempKey = Flip(tempKey);

	if (!result) { result = (str == tempKey); }





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
		if (RotateCheck(str, key))
		{
			match = true;
		}
		else
		{
			string flippedKey = Flip(key);
			if (RotateCheck(str, flippedKey))
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


bool Match(const string& str, const string& key)
{
	bool result = false;
	int cnt = 0;
	int cnt2 = 0;
	bool check1 = false;
	bool check2 = false;
	bool check3 = false;

	cnt = count(str.begin(), str.end(), '#');
	cnt2 = count(key.begin(), key.end(), '#');

	if (cnt == cnt2)
	{
		check1 = true;
	}

	cnt = count(str.begin(), str.end(), '/');
	cnt2 = count(key.begin(), key.end(), '/');

	if (cnt == cnt2)
	{
		check2 = true;
	}

	cnt2 = count(key.begin(), key.end(), '.');
	cnt = count(str.begin(), str.end(), '.');

	if (cnt == cnt2)
	{
		check3 = true;
	}



	return (check1 && check2 && check3);


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

void StrToVec(const string& str, vector<vector<string>>& vec, int currPos)
{
	vector<string> result;
	string temp = str + "/";
	int idx = 0;


	while (vec[idx].size() == currPos)
	{
		++idx;
	}
	while (temp.find_first_of('/') != string::npos)
	{
		vector<string> tempStr;
		int pos = temp.find_first_of('/');
		vec[idx].push_back(temp.substr(0, pos));
		++idx;
		temp.erase(0, pos + 1);
	}

}

void HandleDivisible(string& result, const map<string, string>& rules, int div)
{
	/* 2 = 2x2 -> 3x3 */
	map<int,int> currentPosPerRow;
	string tempResult = result + "/";
	vector<vector<string>> parsedData;
	string finalResult;
	vector<vector<string>> tempVec(5000);
	vector<string> rowVec;
	int amountPerRow = 0;

	while (!tempResult.empty())
	{
		rowVec.push_back(tempResult.substr(0, div));
		tempResult.erase(0, div);

		if (tempResult[0] == '/')
		{
			parsedData.push_back(rowVec);
			tempResult.erase(0, tempResult.find_first_of("/") + 1);
			rowVec.clear();


		}

	}

	amountPerRow = parsedData[0].size();
	int currentRow = 0;
	int processCount = 0;
	while (!all_of(parsedData.begin(), parsedData.end(), [](const vector<string>& innerVec) {return innerVec.empty(); }))
	{
		string combined;
		for (int i = currentRow; i < currentRow + div; ++i)
		{
			combined.append(parsedData[i][0]);
			parsedData[i].erase(parsedData[i].begin());
			if (parsedData[i].empty())
			{
				++processCount;
			}
			combined.append("/");

		}
		combined.pop_back();

		//parsedData.erase(remove_if(parsedData.begin(), parsedData.end(), [](const vector<string>& vec) {return vec.empty(); }), parsedData.end());

		bool match = false;
		for (auto it = rules.begin(); it != rules.end(); ++it)
		{
			string key = it->first;
			string replace = it->second;

			if (KeyValid(combined, key))
			{
				StrToVec(replace, tempVec, amountPerRow);

				it = prev(rules.end());
				match = true;
			}


		}

		if (!match)
		{
			cout << "FAILED PATTERN MATCH";
		}

		if (processCount == div)
		{
			currentRow += div;
			processCount = 0;

		}


	}


	tempVec.erase(remove_if(tempVec.begin(), tempVec.end(), [](const vector<string>& innerVec) {return innerVec.empty(); }), tempVec.end());
	for (int i = 0; i < tempVec.size(); ++i)
	{
		for (int j = 0; j < tempVec[i].size(); ++j)
		{
			finalResult.append(tempVec[i][j]);
		}
		finalResult.append("/");
	}

	finalResult.pop_back();

	result = finalResult;





}


int main()
{
	fstream file; file.open("input.txt");
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


	for (size_t i = 0; i < PART_2_ITERATIONS; ++i)
	{
		int slashCount = count(result.begin(), result.end(), '/');
		if (((result.size() - slashCount) % 2) == 0)
		{
			HandleDivisible(result, rules, 2);
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