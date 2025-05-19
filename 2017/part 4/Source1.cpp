#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_set>



using namespace std;



bool hasAnagram(const string &currentKey, string fullLine)
{
	bool result = false;
	size_t keyLength = currentKey.length();
	fullLine.erase(fullLine.find(currentKey), keyLength);
	stringstream stream(fullLine);
	string tempCurrent;


	while (stream >> tempCurrent && !result)
	{
		int charMatch = 0;
		if (tempCurrent.length() == keyLength)
		{
			for (const char& currentChar : tempCurrent)
			{
				if (currentKey.find(currentChar) != string::npos)
				{
					++charMatch;
				}
			}

			if (charMatch == keyLength)
			{
				result = true;
			}
		}


	}








	return result;

}
int main()
{
	fstream file; file.open("input.txt");
	string line;
	int validPhrases = 0;



	while (getline(file, line))
	{
		stringstream stream(line);
		unordered_set<string> tempSet;
		string currentKey;
		bool skip = false;

		while (stream >> currentKey && !skip)
		{
			if (tempSet.insert(currentKey).second == false)
			{
				skip = true;
			}

			if (!skip)
			{
				if (hasAnagram(currentKey, line))
				{
					skip = true;
				}
			}

		}

		if (!skip)
		{
			++validPhrases;
		}


	}
	cout << validPhrases;

	return 0;
}