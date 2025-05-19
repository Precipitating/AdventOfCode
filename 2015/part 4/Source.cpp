#include <iostream>
#include <bitset>
#include <string>
#include "hashlibpp.h"
#include <string_view>
#include <ppl.h>
//#define _CRT_SECURE_NO_WARNINGS

//using namespace concurrency;

int main()
{
	bool done = false;
	int inputToBinary = 0;
	std::string input = "bgvyzdsv";
	int lowestValue = 0;
	std::string hash;



	hashwrapper* md5Wrap = new md5wrapper;

	do
	{
		hash = md5Wrap->getHashFromString(input + std::to_string(lowestValue));
		std::string_view splitHash = std::string_view(hash.data(), 6);

		if (std::strcmp(std::string(splitHash).c_str(), "000000") == 0)
		{
			done = true;
		}
		else
		{
			++lowestValue;
		}



	} while (!done);






	delete md5Wrap;
	md5Wrap = nullptr;

	std::cout << lowestValue;


	return 0;

}