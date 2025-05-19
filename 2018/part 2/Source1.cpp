#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
	fstream file; file.open("input.txt");
	string line;
	int twoTimes = 0;
	int threeTimes = 0;
	int matchCounter = -1;
	vector<string> data;
	pair<string, string> closestMatches;
	while (getline(file, line))
	{
		if (matchCounter == -1)
		{
			matchCounter = line.size() - 1;
		}

		data.push_back(line);

	}



	/* get possible closest match */
	while (closestMatches.first.empty())
	{
		for (const string& str : data)
		{
			string toMatch = str;
			int perfectMatches = 0;

			for (const string& str1 : data)
			{
				if (closestMatches.first.empty() && closestMatches.second.empty())
				{
					if (str1 != str)
					{
						string possibleMatch = str1;

						for (int i = 0; i < possibleMatch.size(); ++i)
						{
							if (possibleMatch[i] != '*')
							{

								if (possibleMatch[i] == toMatch[i])
								{
									++perfectMatches;
								}

								std::replace(possibleMatch.begin(), possibleMatch.end(), possibleMatch[i], '*');
							}


						}

						if (perfectMatches == matchCounter)
						{
							closestMatches.first = str;
							closestMatches.second = str1;

						}
						else
						{
							perfectMatches = 0;
						}



					}
				}


			}
		}

		if (closestMatches.first.empty())
		{
			--matchCounter;

		}
	}



	/* remove mismatches */


	for (int i = 0; i < closestMatches.first.size(); ++i)
	{
		if (closestMatches.first[i] != closestMatches.second[i])
		{
			closestMatches.first[i] = '*';
		}





	}

	closestMatches.first.erase(remove(closestMatches.first.begin(), closestMatches.first.end(), '*'), closestMatches.first.end());

	cout << closestMatches.first;



	return 0;
}