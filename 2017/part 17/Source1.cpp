#include <iostream>
#include <deque>
#include <algorithm>

using namespace std;

const int INPUT = 382;
const int TEST_INPUT = 3;
const int PART_2_TARGET = 0;

int main()
{
	int currentPos = 0;
	int currentVal = 1;
	deque<int> buffer(1);
	int size = 1;

	for (int i = 0; i < 50000000; ++i)
	{
		int nextPosVal = currentPos + INPUT;
		if (nextPosVal >= size)
		{
			nextPosVal %= size;

		}
		while ((nextPosVal % size) >= size)
		{
			nextPosVal %= size;

		}


		if (nextPosVal + 1 == 1)
		{
			cout << currentVal << '\n';
		}
		++size;



		currentPos = nextPosVal + 1;
		++currentVal;



	}










	return 0;
}