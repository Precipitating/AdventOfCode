#include <iostream>
#include <string>
#include <regex>
#include <vector>
using namespace std;

string ApplyDragonCurve(const string& input)
{
	string inputCopy = { input.rbegin(), input.rend() };

	for (size_t i = 0; i < inputCopy.length(); ++i)
	{
		if (inputCopy[i] == '1')
		{
			inputCopy[i] = '0';
		}
		else
		{
			inputCopy[i] = '1';
		}
	}
	string result = input + '0' + inputCopy;

	return result;
}

void ApplyCheckSum(const string& input)
{
	regex doubleCheck("(11|00)");
	regex mismatchCheck("(01|10)");
	bool found = false;
	string temp = input;
	string result;
	vector<bool> booleanVersion;
	vector<bool> resultBool;
	booleanVersion.reserve(input.size());
	for (const auto& a : input)
	{
		booleanVersion.push_back(a == '1');
	}

	do
	{
		for (size_t i = 0; i < booleanVersion.size(); ++i)
		{
			if ((booleanVersion[i] && booleanVersion[i + 1]) || (!booleanVersion[i] && !booleanVersion[i + 1]))
			{
				resultBool.push_back(true);
				++i;
			}
			else
			{
				resultBool.push_back(false);
				++i;
			}
		}

		if (resultBool.size() % 2 == 0)
		{
			booleanVersion = resultBool;
			resultBool.clear();
		}
		else
		{
			for (const bool x : resultBool)
			{
				if (x)
					cout << '1';
				else
					cout << '0';
			}
			found = true;
		}


	} while (!found);



	

}



int main()
{
	string input = "10001001100000001";
	int fillLength = 272;
	int part2Length = 35651584;
	while (input.size() < part2Length)
	{
		input = ApplyDragonCurve(input);

	}

	/* cut string until desired length */
	input = input.substr(0, part2Length);

	ApplyCheckSum(input);


	return 0;
}