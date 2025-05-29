#include <iostream>
#include <vector>
#include <string>
using namespace std;



int main()
{
	//int input = 440231;
	int elf1 = 0, elf2 = 1;
	vector<int> nums = { 3,7 };
	long long result = 0;


#pragma region PART1
	//while (nums.size() <= input + 10)
	//{
	//	int sum = nums[elf1] + nums[elf2];

	//	// max 2 digits so we divide 10 to extract the next num
	//	if (sum >= 10)
	//	{
	//		nums.push_back(sum / 10);
	//		if (nums.size() > input)
	//		{
	//			result *= 10;
	//			result += nums.back();
	//		}
	//	}
	//	nums.push_back(sum % 10);
	//	if (nums.size() > input)
	//	{
	//		result *= 10;
	//		result += nums.back();

	//	}



	//	elf1 = (elf1 + 1 + nums[elf1]) % nums.size();
	//	elf2 = (elf2 + 1 + nums[elf2]) % nums.size();


	//}

	// note to get first 10 if there's more
	//cout << result;
#pragma endregion

#pragma region PART2
	int consecutiveDigits = 0;
	vector<int> inputToVec;
	string inputToStr = "440231";

	
	// put input to vector for easier handling

	for (char c : inputToStr)
	{
		inputToVec.push_back(c - '0');
	}


	// naive
	while (result == 0)
	{

		int sum = nums[elf1] + nums[elf2];
		vector<int> newDig;

		// max 2 digits so we divide 10 to extract the next num
		if (sum >= 10)
		{
			newDig.push_back(sum / 10);

		}
		newDig.push_back(sum % 10);


		for (int digit : newDig)
		{
			nums.push_back(digit);

			if (nums.size() >= inputToVec.size())
			{
				bool match = true;

				for (size_t i = 0; i < inputToVec.size(); ++i)
				{
					if (nums[nums.size() - inputToVec.size() + i] != inputToVec[i])
					{
						match = false;
						break;
					}
				}

				if (match)
				{
					result = nums.size() - inputToVec.size();
					break;
				}
			}



		}




		elf1 = (elf1 + 1 + nums[elf1]) % nums.size();
		elf2 = (elf2 + 1 + nums[elf2]) % nums.size();


	}

	// note to get first 10 if there's more
	std::cout << result;
#pragma endregion

	return 0;
}