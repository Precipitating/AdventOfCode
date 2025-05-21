#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#pragma region PART1
//int main()
//{
//	fstream file("input.txt");
//	string line;
//	string result;
//	string stack;
//	while (getline(file, line))
//	{
//		stack.push_back(line[0]);
//		for (size_t i = 1; i < line.size(); ++i)
//		{
//			if (!stack.empty() && tolower(line[i]) == tolower(stack.back()) && line[i] != stack.back())
//			{
//				stack.pop_back();
//			}
//			else
//			{
//				stack.push_back(line[i]);
//			}
//		}
//	
//	}
//
//	file.close();
//
//	cout << stack.size();
//	return 0;
//}
#pragma endregion

#pragma region PART2
int main()
{
	fstream file("input.txt");
	string line;
	string inputStr;
	int smallest = INT_MAX;

	while (getline(file, line))
	{
		inputStr.append(line);
	}
	for (char letter = 'a'; letter <= 'z'; ++letter)
	{
		string stack;
		string modified = inputStr;
		modified.erase(remove_if(modified.begin(), modified.end(), [letter](char c) {return tolower(c) == letter; }), modified.end());
		stack.push_back(modified[0]);
		for (size_t i = 1; i < modified.size(); ++i)
		{
			if (!stack.empty() && tolower(modified[i]) == tolower(stack.back()) && modified[i] != stack.back())
			{
				stack.pop_back();
			}
			else
			{
				stack.push_back(modified[i]);
			}
		}
		smallest = min(smallest, (int)stack.size());



	}


	file.close();

	cout << smallest;
	return 0;
}
#pragma endregion