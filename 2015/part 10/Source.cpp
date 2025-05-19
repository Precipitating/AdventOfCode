#include <iostream>
#include <string>





int main()
{

	std::string input = "1113122113";
	std::string result; 
	int counter = 0;
	int currentNumber = -1;
	int processCount = 0;

	for (int i = 0; i < 50; ++i)
	{
		for (std::string::iterator it = input.begin(); it != input.end(); ++it)
		{
			++processCount;
			if (currentNumber == -1)
			{
				currentNumber = std::stoi(std::string(1, *it));

			}

			if (std::stoi(std::string(1, *it)) == currentNumber)
			{
				++counter;
			}
			else
			{
				result.append(std::to_string(counter));
				result.append(std::to_string(currentNumber));
				currentNumber = std::stoi(std::string(1, *it));
				counter = 1;

				if (processCount == input.length())
				{
					result.append(std::to_string(counter));
					result.append(std::to_string(currentNumber));
					
				}
			}




		}


		std::cout << "iteration " << i << " " << result.length() << '\n';

		input = result;
		result.clear();
		counter = 0;
		currentNumber = -1;
		processCount = 0;
	}





	std::cout << result.length();


}