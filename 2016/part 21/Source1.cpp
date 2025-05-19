#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>


using namespace std;

int main()
{
	fstream file; file.open("input.txt");
	string line;
	string input = "fbgdceah";
	vector<string> descrambleList;

	while (getline(file, line))
	{
		descrambleList.push_back(line);

	}
	reverse(descrambleList.begin(), descrambleList.end());


	for (string& currentInstruction : descrambleList)
	{
		if (currentInstruction.find("swap") != string::npos)
		{

			if (currentInstruction.find("letter") != string::npos)
			{
				currentInstruction.erase(0, 12);
				currentInstruction.erase(1, currentInstruction.size() - 2);
				size_t swap1 = input.find(currentInstruction[0]);
				size_t swap2 = input.find(currentInstruction[1]);

				input[swap2] = currentInstruction[0];
				input[swap1] = currentInstruction[1];
			}
			else if (currentInstruction.find("position") != string::npos)
			{
				currentInstruction.erase(0, 14);
				currentInstruction.erase(1, currentInstruction.size() - 2);

				size_t pos1 = currentInstruction[0] - '0';
				size_t pos2 = currentInstruction[1] - '0';


				char char1 = input[currentInstruction[0] - '0'];
				char char2 = input[currentInstruction[1] - '0'];

				input[pos2] = char1;
				input[pos1] = char2;


			}

		}
		else if (currentInstruction.find("rotate") != string::npos)
		{
			if (currentInstruction.find("based") != string::npos)
			{
				for (int i = 1; i < input.length() + 2; ++i)
				{

					string tempHash = input;

					if (i > input.length())
					{
						rotate(tempHash.begin(), tempHash.begin() + 2, tempHash.end());
						rotate(tempHash.begin(), tempHash.begin() + (i - 2), tempHash.end());


					}
					else
					{
						rotate(tempHash.begin(), tempHash.begin() + i, tempHash.end());
					}
					
					currentInstruction.erase(0, currentInstruction.size() - 1);

					size_t pos = tempHash.find(currentInstruction[0]);

					int rotateRightAmount = pos;

					string potentialDescrambleInput = tempHash;


					rotate(potentialDescrambleInput.begin(), potentialDescrambleInput.begin() + potentialDescrambleInput.size() - 1, potentialDescrambleInput.end());
					rotate(potentialDescrambleInput.begin(), potentialDescrambleInput.begin() + potentialDescrambleInput.size() - pos, potentialDescrambleInput.end());
					if (rotateRightAmount + 1 > 4)
					{
						rotate(potentialDescrambleInput.begin(), potentialDescrambleInput.begin() + potentialDescrambleInput.size() - 1, potentialDescrambleInput.end());
					}


					if (potentialDescrambleInput == input)
					{
						input = tempHash;
						break;
					}

				}




			}
			else if (currentInstruction.find("right") != string::npos)
			{
				currentInstruction.erase(0, 13);

				int rotateRightAmount = currentInstruction[0] - '0';

				rotate(input.begin(), input.begin() + rotateRightAmount, input.end());



			}
			else if (currentInstruction.find("left") != string::npos)
			{
				currentInstruction.erase(0, 12);

				int rotateLeftAmount = currentInstruction[0] - '0';

				rotate(input.begin(), input.begin() + input.size() - rotateLeftAmount, input.end());




			}
		}
		else if (currentInstruction.find("reverse") != string::npos)
		{
			currentInstruction.erase(0, 18);
			currentInstruction.erase(1, 9);

			string reversed = input;
			int from = currentInstruction[0] - '0';
			int to = currentInstruction[1] - '0';

			reversed = reversed.substr(from, (to - from) + 1);
			reversed = { reversed.rbegin(), reversed.rend() };

			input.replace(from, (to - from) + 1, reversed);


		}
		else if (currentInstruction.find("move") != string::npos)
		{
			currentInstruction.erase(0, 14);
			currentInstruction.erase(1, currentInstruction.size() - 2);

			char charToInsert = input[currentInstruction[1] - '0'];

			input.erase(currentInstruction[1] - '0', 1);


			if ((currentInstruction[0] - '0') > input.length())
			{
				input.append(string(1, charToInsert));
			}
			else
			{
				input.insert(currentInstruction[0] - '0', 1, charToInsert);
			}


		}
	}
	
	cout << input;

	return 0;
}