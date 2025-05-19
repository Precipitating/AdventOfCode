#include <iostream>
#include "hashlibpp.h"
#include <regex>
using namespace std;



int main()
{
	regex sameCharFilter("(.)\\1{2}");
	string hash;
	string input = "cuanljph";
	//string input2 = "abc";

	int counter = 0;
	hashwrapper* md5Wrap = new md5wrapper;

	int correctHash = 0;
	bool finished = false;

	smatch match;

	while (!finished)
	{

		hash = md5Wrap->getHashFromString(input + std::to_string(counter));

		if (regex_search(hash,match,sameCharFilter))
		{
			string fiveCharCheck;
			fiveCharCheck.insert(0, 5, hash[match.position()]);

			regex fiveVersion(fiveCharCheck);

			int i = counter + 1;
			bool found = false;
			while (i <= (counter + 1000) && !found)
			{
				string newHash = md5Wrap->getHashFromString(input + std::to_string(i));
				if (regex_search(newHash, fiveVersion))
				{
					++correctHash;
					found = true;
				}
				else
				{
					++i;
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