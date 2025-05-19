#include <iostream>
#include <string>
#include <regex>
#include "md5.h"
using namespace std;



int main()
{
	regex zeroSearch("00000");
	string answer;
	int index = 0;
	string input = "cxdnnyjw";
	string currentID = input + to_string(index);
	string md5Hash = md5(currentID);
	string shortenedHash = md5Hash.substr(0, 5);
	string currentHash;
	std::smatch match;
	int matchCount = 0;

	while (matchCount != 8)
	{
		while (!regex_search(shortenedHash, match, zeroSearch))
		{
			++index;
			shortenedHash = md5(input + to_string(index));
			currentHash = shortenedHash;
			shortenedHash = shortenedHash.substr(0, 5);

		}

		answer.append(string(1,currentHash[5]));
		++matchCount;

		++index;
		shortenedHash = md5(input + to_string(index));
		shortenedHash = shortenedHash.substr(0, 5);

	}

	cout << answer;




}