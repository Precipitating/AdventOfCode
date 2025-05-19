#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	fstream file; file.open("input.txt");
	string line;
	int validTriangle = 0;

	while (getline(file, line))
	{
		int input1, input2, input3;
		stringstream stream(line);

		while (stream >> input1 >> input2 >> input3)
		{
			vector<int> tempVector = { input1, input2,input3 };
			/* first smallest element*/
			input1 = *min_element(tempVector.begin(), tempVector.end());
			tempVector.erase(remove(tempVector.begin(), tempVector.end(), *min_element(tempVector.begin(), tempVector.end())));
			/* second smallest element*/
			input2 = *min_element(tempVector.begin(), tempVector.end());
			tempVector.erase(remove(tempVector.begin(), tempVector.end(), *min_element(tempVector.begin(), tempVector.end())));

			/* last element should be the highest*/
			input3 = tempVector[0];

			
			if ((input1 + input2) > input3)
			{
				++validTriangle;
			}
		}

	}

	cout << validTriangle;
	return 0;
}