#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <utility>

void RemoveWordFromLine(std::string& line, const std::string& word)
{
	auto n = line.find(word);
	if (n != std::string::npos)
	{
		line.erase(n, word.length());
	}
}

std::string GetWireName(const std::string& line, std::map<std::string, int>& wireVec)
{
	std::string tempLine = line;
	auto n = tempLine.find(">");
	++n;

	if (n != std::string::npos)
	{
		tempLine.erase(tempLine.begin(), tempLine.begin() + n);
	}

	std::stringstream stream(tempLine);

	std::string var;

	stream >> var;

	wireVec.insert({ var, -1 });
	

	return var;


}

std::string GateExtractor(const std::string& line)
{
	std::string tempLine = line;
	std::string gate;
	int value;

	for (size_t i = 0; i < tempLine.size(); ++i)
	{
		if (std::isupper(tempLine[i]))
		{
			for (size_t j = i, counter = 0; i < tempLine.size(); ++j, ++counter)
			{
				if (std::isspace(tempLine[j]))
				{

					gate = tempLine.substr(i, counter);

					if ( (strstr(gate.c_str(), "LSHIFT") || (strstr(gate.c_str(), "RSHIFT"))))
					{
						gate = tempLine.substr(i, counter + 3);
					}

					break;
				}



			}
			break;
		}

		
	}




	return gate;


}

void GetInputs(const std::string& gate, const std::string& line, const std::string& wireName, std::map<std::string, int>& wireVec)
{
	std::string tempLine = line;
	std::stringstream temp(gate);

	std::string input;
	int input2;

	temp >> input >> input2;

	if (strstr(input.c_str(), "LSHIFT") || strstr(input.c_str(), "RSHIFT"))
	{
		/* seperate the only input as shifts only supply 1 */
		RemoveWordFromLine(tempLine, input);
		RemoveWordFromLine(tempLine, std::to_string(input2));
		RemoveWordFromLine(tempLine, "->");
		RemoveWordFromLine(tempLine, wireName);

		std::stringstream extractedInputs(tempLine);

		std::string inputA;

		extractedInputs >> inputA;


		if (strstr(input.c_str(), "LSHIFT"))
		{
			if (wireVec.count(inputA) == 1)
			{
				if (wireVec[inputA] != 0)
				{
					wireVec[wireName] = wireVec[inputA] << input2;
				}
			}

		}
		else if (strstr(input.c_str(), "RSHIFT"))
		{
			if (wireVec.count(inputA) == 1)
			{
				if (wireVec[inputA] != 0)
				{
					wireVec[wireName] = wireVec[inputA] >> input2;
				}
			}
		}
		
		

	}
	else if (strstr(input.c_str(), "AND"))
	{
		RemoveWordFromLine(tempLine, input);
		RemoveWordFromLine(tempLine, std::to_string(input2));
		RemoveWordFromLine(tempLine, "->");
		RemoveWordFromLine(tempLine, wireName);



		std::stringstream stream(tempLine);
		std::string inputA;
		std::string inputB;
		int digit1 = -1, digit2 = -1;

		stream >> inputA >> inputB;

		if (isdigit(inputA[0]))
		{
			digit1 = std::stoi(inputA);


		}
		if (isdigit(inputB[0]))
		{
			digit2 = std::stoi(inputB);
		}




		if (digit1 != -1 && digit2 != -1)
		{
			wireVec[wireName] = digit1 & digit2;
		}
		else if (digit1 != -1 && digit2 == 0)
		{
			if (wireVec.count(inputB) == 1)
			{
				if (wireVec[inputB] != 0)
				{
					wireVec[wireName] = digit1 & wireVec[inputB];
				}
			}

		}
		else if (digit1 == 0 && digit2 != 0)
		{
			if (wireVec.count(inputB) == 1)
			{
				if (wireVec[inputB] != 0)
				{
					wireVec[wireName] = digit1 & wireVec[inputB];
				}
			}

		}
		else
		{
			if (wireVec.count(inputA) == 1 && wireVec.count(inputA) == 1)
			{
				if (wireVec[inputA] != 0 && wireVec[inputB] != 0)
				{
					wireVec[wireName] = wireVec[inputA] & wireVec[inputB];
				}
			}

		}




	}
	else if (strstr(input.c_str(), "NOT"))
	{
		RemoveWordFromLine(tempLine, input);

		std::stringstream stream(tempLine);

		std::string input;

		stream >> input;

		if (wireVec.count(input) == 1)
		{
			if (wireVec[input] != 0)
			{
				wireVec[wireName] = ~wireVec[input];
			}
			
		}


	}
	else if (strstr(input.c_str(), "OR"))
	{
		RemoveWordFromLine(tempLine, input);

		std::stringstream stream(tempLine);

		std::string inputA, inputB;

		stream >> inputA >> inputB;

		if (wireVec.count(inputA) == 1 && wireVec.count(inputB) == 1)
		{
			if (wireVec[inputA] != 0 && wireVec[inputB] != 0)
			{
				wireVec[wireName] = wireVec[inputA] | wireVec[inputB];
			}
		}

	}
	else
	{
		std::stringstream stream(tempLine);

		if (isdigit(tempLine[0]))
		{
			int value;

			stream >> value;

			if (wireVec[wireName] == 0)
			{
				wireVec[wireName] = value;
			}


		}
		else
		{
			std::stringstream stream(tempLine);
			std::string str;

			stream >> str;


			if (wireVec.count(str) == 1)
			{
				if (wireVec[str] != 0)
				{
					wireVec[wireName] = wireVec[str];
				}
			}

		}


	}








}

int main()
{
	std::ifstream file;
	file.open("input.txt");
	std::string line;
	std::map<std::string, int> wires;


	for (int i = 0; i < 9999; ++i)
	{
		while (getline(file, line))
		{

			GetInputs(GateExtractor(line), line, GetWireName(line, wires), wires);


		}

		file.clear();
		file.seekg(0);
	}



	return 0;
}