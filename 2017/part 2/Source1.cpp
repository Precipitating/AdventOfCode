#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;



int main()
{
	fstream file; file.open("input.txt");
	string line;
	int answer = 0;

	vector<int> row;
	while (getline(file, line))
	{
		int currentNum;

		stringstream stream(line);

		while (stream >> currentNum)
		{
			row.push_back(currentNum);

		}


		int dividedNum = 0;


		for (int i = 0; i < row.size(); ++i)
		{
			int& currentNum = row[i];

			for (int j = 0; j < row.size(); ++j)
			{
				if (j != i)
				{
					int& otherNum = row[j];
					if (currentNum % otherNum == 0)
					{
						dividedNum = currentNum / otherNum;
						goto out;
					
					}

				}

			}


		}
		out:


		answer += dividedNum;


		row.clear();

	}

	cout << answer;

	return 0;
}