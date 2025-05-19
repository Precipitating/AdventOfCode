#include <iostream>
#include <string>
#include <regex>
#include "md5.h"
using namespace std;



int main()
{
	regex zeroSearch("^00000[0-7]");
	regex xSearch("x");
	string answer = "xxxxxxxx";
	int index = 0;
	string input = "cxdnnyjw";
	string currentID = input + to_string(index);
	string md5Hash = md5(currentID);
	string shortenedHash = md5Hash.substr(0, 6);
	string currentHash;
	std::smatch match;
	int matchCount = 0;

	while (regex_search(answer, xSearch))
	{
		while (!regex_search(shortenedHash, match, zeroSearch))
		{
			++index;
			shortenedHash = md5(input + to_string(index));
			currentHash = shortenedHash;
			shortenedHash = shortenedHash.substr(0, 6);

		}
		if (answer[currentHash[5] - '0'] == 'x')
		{
			answer[currentHash[5] - '0'] = currentHash[6];
		}
		++matchCount;

		++index;
		shortenedHash = md5(input + to_string(index));
		shortenedHash = shortenedHash.substr(0, 6);

	}

	cout << answer;




}