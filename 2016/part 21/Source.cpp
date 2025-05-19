#include <iostream>
#include <string>
#include <sstream>
#include <fstream>


using namespace std;

int main()
{
	fstream file; file.open("input.txt");
	string line;
	string input = "abcdefgh";
	

	while (getline(file, line))
	{
		if (line.find("swap") != string::npos)
		{

			if (line.find("letter") != string::npos)
			{
				line.erase(0, 12);
				line.erase(1, line.size() - 2);
				size_t swap1 = input.find(line[0]);
				size_t swap2 = input.find(line[1]);

				input[swap2] = line[0];
				input[swap1] = line[1];
			}
			else if (line.find("position") != string::npos)
			{
				line.erase(0, 14);
				line.erase(1, line.size() - 2);

				size_t pos1 = line[0] - '0';
				size_t pos2 = line[1] - '0';


				char char1 = input[line[0] - '0'];
				char char2 = input[line[1] - '0'];

				input[pos2] = char1;
				input[pos1] = char2;


			}

		}
		else if (line.find("rotate") != string::npos)
		{
			if (line.find("based") != string::npos)
			{
				line.erase(0, line.size() - 1);

				size_t pos = input.find(line[0]);

				int rotateRightAmount = pos;



				rotate(input.begin(), input.begin() + input.size() - 1, input.end());
				rotate(input.begin(), input.begin() + input.size() - rotateRightAmount, input.end());
				if (rotateRightAmount + 1 > 4)
				{
					rotate(input.begin(), input.begin() + input.size() - 1, input.end());
				}




			}
			else if (line.find("right") != string::npos)
			{
				line.erase(0, 13);

				int rotateRightAmount = line[0] - '0';

				rotate(input.begin(), input.begin() + input.size() - rotateRightAmount, input.end());



			}
			else if (line.find("left") != string::npos)
			{
				line.erase(0, 12);

				int rotateLeftAmount = line[0] - '0';

				rotate(input.begin(), input.begin() + rotateLeftAmount, input.end());




			}
		}
		else if (line.find("reverse") != string::npos)
		{
			line.erase(0, 18);
			line.erase(1, 9);

			string reversed = input;
			int from = line[0] - '0';
			int to = line[1] - '0';

			reversed = reversed.substr(from, (to - from) + 1);
			reversed = { reversed.rbegin(), reversed.rend() };

			input.replace(from,(to - from) + 1, reversed);


		}
		else if (line.find("move") != string::npos)
		{
			line.erase(0, 14);
			line.erase(1, line.size() - 2);

			char charToInsert = input[line[0] - '0'];

			input.erase(line[0] - '0', 1);


			if ((line[1] - '0') > input.length())
			{
				input.append(string(1,charToInsert));
			}
			else
			{
				input.insert(line[1] - '0', 1, charToInsert);
			}


		}

	}

	cout << input;

	return 0;
}