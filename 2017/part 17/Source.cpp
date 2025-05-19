#include <iostream>
#include <deque>
#include <algorithm>

using namespace std;

const int INPUT = 382;
const int TEST_INPUT = 3;
const int PART_1_TARGET = 2017;

int main()
{
	int currentPos = 0;
	int currentVal = 1;
	deque<int> buffer(1);

	for (int i = 0; i < PART_1_TARGET; ++i)
	{
		
		int nextPosVal = currentPos + INPUT;
		if (nextPosVal >= buffer.size())
		{
			nextPosVal %= buffer.size();

		}
		while ((nextPosVal % buffer.size()) >= buffer.size())
		{
			nextPosVal %= buffer.size();

		}

		buffer.insert(buffer.begin() + (nextPosVal + 1) , currentVal);


		currentPos = nextPosVal + 1;
		++currentVal;


	}



	auto part1Answer = find(buffer.begin(), buffer.end(), PART_1_TARGET);
	++part1Answer;

	cout << *part1Answer;








	return 0;
}