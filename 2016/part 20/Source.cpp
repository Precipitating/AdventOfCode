#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <set>
#include <regex>
#include <vector>



using namespace std;
const long long maxNum = 4294967295;
int main()
{
	vector<bool> blockedNumbers(maxNum);
	fstream file; file.open("input.txt");
	string line;
	regex hyphenRemover("-");
	while (getline(file, line))
	{
		long long startRange;
		long long endRange;
		line = regex_replace(line, hyphenRemover, " ");

		stringstream stream(line);

		stream >> startRange >> endRange;
		++endRange;


		for (long long i = startRange; i < endRange; ++i)
		{
			blockedNumbers[i] = true;
		}
	}

	bool found = false;
	/* part 1 = the first push back is the lowest accepted IP*/
	for (long long i = 0; !found; ++i)
	{
		if (!blockedNumbers[i] )
		{
			cout << i << '\n';
			found = true;

		}
	}

	/* part 2 */
	long long cnt = count_if(blockedNumbers.begin(), blockedNumbers.end(), [](bool x) {return !x; });

	cout << cnt;



	return 0;






}