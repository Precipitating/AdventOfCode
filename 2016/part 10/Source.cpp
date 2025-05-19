#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include <map>
#include <algorithm>

using namespace std;


void ProcessValue(int botID, int value, map<int, vector<int>>& map)
{
	map[botID].push_back(value);



}

int main()
{
	regex givingFilter("gives");
	regex givingLowOutputFilter("low to output");
	regex givingHighOutputFilter("high to output");
	regex valueFilter("value");

	fstream file; file.open("input.txt");
	string line;
	map<int, vector<int>> botMap;
	vector<pair<int,vector<int>>> outputBin;

	int numberOfExecutions = 0;
	bool initialValuesSet = false;


	while (numberOfExecutions != 231)
	{
		while (getline(file, line))
		{
			if (regex_search(line, valueFilter))
			{
				int value, botID;
				regex fluffFilter("value|goes|to|bot");
				line = regex_replace(line, fluffFilter, "");
				stringstream stream(line);

				stream >> value >> botID;

				if(botMap[botID].size() < 2)
				{
					ProcessValue(botID, value, botMap);
				}

				++numberOfExecutions;
			}

			else
			{

				int botID = 0;
				size_t botPos = line.find_first_of("t");
				string tempLine = line.substr(botPos + 2);
				stringstream stream(tempLine);

				/* get giver ID*/
				stream >> botID;

				/* get botID lowest value*/
				int lowestVal = -1;
				int highestVal = -1;
				if (botMap[botID].size() == 2)
				{
					lowestVal = *min_element(botMap[botID].begin(), botMap[botID].end());
					highestVal = *max_element(botMap[botID].begin(), botMap[botID].end());

					botMap[botID].erase(remove(botMap[botID].begin(), botMap[botID].end(), lowestVal), botMap[botID].end());
					botMap[botID].erase(remove(botMap[botID].begin(), botMap[botID].end(), highestVal), botMap[botID].end());

					/* get receiver ID and determine if its gonna be output or bot */
					botPos = tempLine.find_first_of("o") + 1;
					tempLine = tempLine.substr(botPos);
					botPos = tempLine.find_first_of("o") + 2;
					tempLine = tempLine.substr(botPos);

					string botOrOutput;
					int outputOrID;
					stringstream updatedStream(tempLine);
					updatedStream >> botOrOutput >> outputOrID;

					/* receive the value .. if the value exists and isnt -1 */
					if (lowestVal != -1)
					{
						if (botOrOutput == "bot")
						{
							if (botMap[outputOrID].size() < 2)
							{
								botMap[outputOrID].push_back(lowestVal);
							}

						}
						else
						{
							/* add it if its empty*/
							if (outputBin.empty())
							{
								outputBin.push_back(make_pair(outputOrID, vector<int>()));
								outputBin.back().second.push_back(lowestVal);
							}
							else
							{
								bool found = false;
								/* check if key exists already*/
								for (int i = 0; i < outputBin.size(); ++i)
								{
									if (outputBin[i].first == outputOrID)
									{
										outputBin[i].second.push_back(lowestVal);
										found = true;
									}
								}

								if (!found)
								{
									outputBin.push_back(make_pair(outputOrID, vector<int>()));
									outputBin.back().second.push_back(lowestVal);
								}

							}
						}

						/* give high value to another bot/output*/

						botPos = tempLine.find_first_of("o") + 1;
						tempLine = tempLine.substr(botPos);
						botPos = tempLine.find_first_of("o") + 2;
						tempLine = tempLine.substr(botPos);

						stringstream updatedStream1(tempLine);
						updatedStream1 >> botOrOutput >> outputOrID;

						/* receive the value .. if the value exists and isnt -1 */
						if (highestVal != -1)
						{
							if (botOrOutput == "bot")
							{
								if (botMap[outputOrID].size() < 2)
								{
									botMap[outputOrID].push_back(highestVal);
								}

							}
							else
							{
								/* add it if its empty*/
								if (outputBin.empty())
								{
									outputBin.push_back(make_pair(outputOrID, vector<int>()));
									outputBin.back().second.push_back(highestVal);
								}
								else
								{
									bool found = false;
									/* check if key exists already*/
									for (int i = 0; i < outputBin.size(); ++i)
									{
										if (outputBin[i].first == outputOrID)
										{
											outputBin[i].second.push_back(highestVal);
											found = true;
										}
									}

									if (!found)
									{
										outputBin.push_back(make_pair(outputOrID, vector<int>()));
										outputBin.back().second.push_back(highestVal);
									}

								}
							}

						
						}



					}

					++numberOfExecutions;
				}


			}

		}
		initialValuesSet = true;

		if (numberOfExecutions != 231)
		{
			file.clear();
			file.seekg(0);
			numberOfExecutions = 0;
		}

	}
	std::sort(outputBin.begin(), outputBin.end());
	int first = 0, second = 0, third = 0;
	for (auto it = outputBin.begin(); it != outputBin.end(); ++it)
	{

			if (it->first == 0)
			{
				first = it->second.back();
			}
			else if (it->first == 1)
			{
				second = it->second.back();
			}
			else if (it->first == 2)
			{
				third = it->second.back();
			}


	}
	if (first != 0 && second != 0 && third != 0)
	{
		cout << first * second * third << '\n';
	}
	return 0;


}