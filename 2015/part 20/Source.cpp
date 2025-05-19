#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;
int visited[9999999]{ 0 };
vector<vector<int>> test;
int FactorFinder(int x)
{
	int num = 1;
	int finalNum = 0;

	//vector<int> lol;
	while (num * num <= x)
	{
		if (x % num == 0)
		{
			if (visited[num] < 50)
			{
				finalNum += num * 11;
				visited[num] += 1;
			}

			if (x / num != num)
			{
				if (visited[x / num] < 50)
				{
					finalNum += (x / num) * 11;
					//lol.push_back(x / num);
					visited[x / num] += 1;
				}
			}

			//lol.push_back(num);



		}
		++num;
	}
	//test.push_back(lol);
	return finalNum;
}

int main()
{
	long input = 34000000;

	for (int i = 1; i < INT_MAX; ++i)
	{
		//cout << FactorFinder(i) << '\n';
		if (FactorFinder(i) > input)
		{
			cout << i << '\n';
		}


	}









	return 0;
}