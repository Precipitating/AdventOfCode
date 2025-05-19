#include <iostream>
#include <string>
#include <array>
#include <algorithm>
#include <regex>


struct ForbiddenFunctor
{
	int operator() (char c)
	{
		bool isForbidden = c == 'i' || c == 'o' || c == 'l';

		return isForbidden;
	}
};

bool ForbiddenCharacterCheck(const std::string& input)
{
	bool result = false;

	result = std::any_of(input.begin(), input.end(), ForbiddenFunctor());

	return result;


}

bool PairChecker(const std::string& input)
{
	bool result = false;

	std::regex overlapCheck("(.)\\1");


	std::sregex_iterator it(input.begin(), input.end(), overlapCheck);
	std::sregex_iterator end;


	if (std::distance(it, end) == 2)
	{
		result = true;
	}


	return result;


}

bool AlphabetCheck(const std::string& input)
{
	bool result = false;
	for (size_t i = 0; i < 6; ++i)
	{
		bool compareOneToTwo = input[i + 1] - input[i] == 1;
		bool compareTwoToThree = input[i + 2] - input[i + 1] == 1;

		if (compareOneToTwo && compareTwoToThree)
		{
			result = true;
			break;
		}


	}

	return result;
}

void InputIncrementer(std::string& input)
{

	bool stop = false;
	std::string::reverse_iterator end = input.rbegin();
	std::string::reverse_iterator start = input.rend();


	while (end != start && !stop )
	{
		if (*end == 'z')
		{
			*end = 'a';
			++end;
			
		}
		else
		{
			*end += 1;
			stop = true;
		}



	}







}

int main()
{

	//std::string input = "vzbxkghb";
	std::string input2 = "vzbxxyzz";

	/* find next one by just incrementing so we get an invalid one  (part 2) */
	InputIncrementer(input2);

	while (!AlphabetCheck(input2) || !PairChecker(input2) || ForbiddenCharacterCheck(input2))
	{
		InputIncrementer(input2);
	}



	std::cout << input2;

	std::string newInput;

	return 0;

}