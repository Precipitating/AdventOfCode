#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_set>


using namespace std;




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

		}

		if (!skip)
		{
			++validPhrases;
		}


	}
	cout << validPhrases;

	return 0;
}