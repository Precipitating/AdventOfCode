#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <regex>
#include <string>
using namespace std;



int main()
{
	fstream file; file.open("input.txt");
	string line;
	vector<int> values;
	vector<int> sequence;
	values.reserve(256);
	//values.reserve(5);
	int skipSize = 0;
	int position = 0;

	/* parse data and initialize */
	for (int i = 0; i < 256; ++i)
	{
		values.push_back(i);
	}
	 
	//for (int i = 0; i < 5; ++i)
	//{
	//	values.push_back(i);
	//}

	while (getline(file, line))
	{
		line = regex_replace(line, regex(","), " ");
		stringstream stream(line);
		int num;

		while (stream >> num)
		{
			sequence.push_back(num);
		}

	}

	/* process */
	for (size_t i = 0; i < sequence.size(); ++i)
	{

		if ((position + sequence[i]) < values.size() - 1)
		{
			reverse(values.begin() + position, (values.begin() + position) + sequence[i]);
		}
		else
		{
			int length = sequence[i];
			vector<int> rotatedVec = values;
			vector<int> finalResult;

			for (int i = position; length != 0; ++i)
			{
				if (i == values.size())
				{
					rotate(rotatedVec.begin(), rotatedVec.begin() + 1, rotatedVec.end());
					--i;
				}

				finalResult.push_back(rotatedVec[i]);
				--length;

			}

			reverse(finalResult.begin(), finalResult.end());

			int rotateAmount = 0;

			for (int i = position; !finalResult.empty(); ++i)
			{
				if (i == values.size())
				{
					rotate(values.begin(), values.begin() + 1, values.end());
					++rotateAmount;
					--i;
				}
				values[i] = finalResult[0];
				finalResult.erase(finalResult.begin());
			}

			rotate(values.rbegin(), values.rbegin() + rotateAmount, values.rend());




		}

		int nextPos = position + sequence[i] + skipSize;
		while (nextPos > (values.size() - 1))
		{
			nextPos -= values.size();
		}
		if (nextPos != position)
		{
			position = nextPos;
		}

		++skipSize;



	}


	cout << values[0] * values[1];



	return 0;
}