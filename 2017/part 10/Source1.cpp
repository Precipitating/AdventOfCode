#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <regex>
#include <string>
#include <functional>
#include <numeric>
#include <iomanip>
using namespace std;



int main()
{
	fstream file; file.open("test.txt");
	string line;
	vector<int> values(256);
	vector<int> sequence;
	//values.reserve(5);
	int skipSize = 0;
	int position = 0;

	/* parse data and initialize */
	for (int i = 0; i < 256; ++i)
	{
		values[i] = i;
	}


	while (getline(file, line))
	{
		stringstream stream(line);
		char num;

		while (stream >> num)
		{
			sequence.push_back(num);
		}

	}

	sequence.insert(sequence.end(), {17, 31, 73, 47, 23});

	/* process */

	for (int round = 0; round < 64; ++round)
	{
		for (size_t i = 0; i < sequence.size(); ++i)
		{

			int currentSequence = sequence[i];
			vector<int> selectedRange;
			int offset = position;


			if (position + sequence[i] > values.size() - 1)
			{
				copy(values.begin() + position, values.end(), back_inserter(selectedRange));
				int dist = distance(values.begin() + position, values.end());
				copy(values.begin(), values.begin() + (sequence[i] - dist), back_inserter(selectedRange));
				reverse(selectedRange.begin(), selectedRange.end());

			}
			else
			{
				if (sequence[i] != 1)
				{
					selectedRange = { values.begin() + position, values.begin() + position + sequence[i] };
					reverse(selectedRange.begin(), selectedRange.end());
				}


			}


			if (selectedRange.size() > 0)
			{
				bool done = false;
				int pos = position;

				for (const int& val : selectedRange)
				{
					if (pos > values.size() - 1)
					{
						pos = 0;
					}
					values[pos] = val;
					++pos;
				}
			}


			selectedRange.clear();
			position += sequence[i] + skipSize;
			if (position > values.size() - 1)
			{
				position %= values.size();
			}
			++skipSize;



		}


	}
	vector<int> sparseHash;


	int curr = 0;
	while (curr != values.size())
	{
		int acc = accumulate(values.begin() + curr, values.begin() + curr + 16, 0, std::bit_xor<int>());
		sparseHash.push_back(acc);
		curr += 16;
	}




	string finalResult;
	for (const int& val : sparseHash)
	{
		stringstream stream;
		stream << std::hex << val;
		finalResult.append(stream.str());

	}


	cout << finalResult;

	return 0;
}