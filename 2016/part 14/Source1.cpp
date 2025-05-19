#include <iostream>
#include "hashlibpp.h"
#include <regex>
#include <vector>
using namespace std;



int main()
{
	regex sameCharFilter("(.)\\1{2}");
	string hash;
	string input = "cuanljph";
	string input2 = "abc";

	int counter = 0;
	hashwrapper* md5Wrap = new md5wrapper;

	int correctHash = 0;
	bool finished = false;

	smatch match;

	vector<string> cachedHashes;
	cachedHashes.reserve(5000);


	for (size_t i = 0; i < 30000; ++i)
	{
		hash = md5Wrap->getHashFromString(input + std::to_string(i));	
		for (size_t i = 0; i < 2016; ++i)
		{
			hash = md5Wrap->getHashFromString(hash);
		}

		cachedHashes.push_back(hash);

	}



	while (!finished)
	{
		if (regex_search(cachedHashes[counter], match, sameCharFilter))
		{
			string fiveCharCheck;
			fiveCharCheck.insert(0, 5, cachedHashes[counter][match.position()]);

			regex fiveVersion(fiveCharCheck);

			int j = counter + 1;
			bool found = false;
			while (j <= (counter + 1000) && !found)
			{
				string& newHash = cachedHashes[j];

				if (regex_search(newHash, fiveVersion))
				{
					++correctHash;
					found = true;
				}
				else
				{
					++j;
				}

			}

		}
		if (correctHash == 64)
		{
			cout << counter << '\n';
			finished = true;
		}
		++counter;

	}




	delete md5Wrap;
	md5Wrap = nullptr;



	return 0;
}