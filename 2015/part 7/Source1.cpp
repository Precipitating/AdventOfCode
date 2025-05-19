#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <utility>
#include <vector>

enum Gate
{
	NONE,
	AND,
	OR,
	NOT,
	RSHIFT,
	LSHIFT
};
std::string GetGate(const std::vector<std::string>& vec, std::map<std::string, int>& wires)
{


	std::string gate;

	/* get gate */
	for (size_t i = 0, j = 0; (i < vec.size() && j != 1); ++i)
	{
		if (isupper(vec[i][0]))
		{
			gate = vec[i];
			j = 1;
		}

	}


	return gate;

}

std::string GetSignal(const std::vector<std::string>& vec, std::map<std::string, int>& wires)
{
	std::string signal;

	/* get signal */
	for (size_t i = 0, j = 0; (i < vec.size() && j != 1); ++i)
	{
		if (strstr(vec[i].c_str(), "->") )
		{
			signal = vec[i + 1];

			if (wires.count(signal) != 1)
			{
				wires.insert({ signal, -69 });
			}
			j = 1;
		}

	}

	return signal;

}

int GateToEnum(const std::string& gate)
{
	Gate gates;

	if (strstr(gate.c_str(), "AND") )
	{
		gates = AND;
	}
	else if (strstr(gate.c_str(), "OR") )
	{
		gates = OR;
	}
	else if (strstr(gate.c_str(), "NOT") )
	{
		gates = NOT;
	}
	else if (strstr(gate.c_str(), "LSHIFT") )
	{
		gates = LSHIFT;
	}
	else if (strstr(gate.c_str(), "RSHIFT") )
	{
		gates = RSHIFT;
	}
	else
	{
		gates = NONE;
	}

	return static_cast<int>(gates);
}

void HandleAnd(const std::string& signal, const std::string& signalA, const std::string& signalB, std::map<std::string, int> &map )
{
	int a = -69, b = -69;
	if (isdigit(signalA[0]))
	{
		a = std::stoi(signalA);
		
	}
	if (isdigit(signalB[0]))
	{
		b = std::stoi(signalB);
	}

	/* if both signals aren't digits, do it */
	if (a == -69 && b == -69)
	{
		if (map[signalA] != -69 && map[signalB] != -69)
		{
			map[signal] = map[signalA] & map[signalB];
		}
	}
	/* if 'a' is a digit, do it with B (if b has already beeen evaluated) */
	else if (a != -69)
	{
		if (map[signalB] != -69)
		{
			map[signal] = a & map[signalB];

		}
	}


};

void HandleNoGate(const std::string& inputA, const std::string& signal, std::map<std::string, int> &map)
{
	if (isdigit(inputA[0]))
	{
		/* part 2 code, delete if want the result of input.txt*/
		if (strstr(signal.c_str(), "b"))
		{
			map[signal] = 3176;
		}
		/* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */
		else
		{
			map[signal] = std::stoi(inputA);
		}
		
	}
	else
	{
		if (map[inputA] != -69)
		{
			map[signal] = map[inputA];
		}
	}
}

void HandleOr(const std::string& signal, const std::string& signalA, const std::string& signalB, std::map<std::string, int>& map)
{
	if (map[signalA] != -69 && map[signalB] != -69)
	{
		map[signal] = map[signalA] | map[signalB];
	}
}

void HandleNot(const std::string& signal, const std::string& signalB, std::map<std::string, int>& map)
{

	if (map[signalB] != -69)
	{
		map[signal] = ~map[signalB];
	}
}
void HandleLShift(const std::string& signal, const std::string& signalA, int shiftNum, std::map<std::string, int>& map)
{
	if (map[signalA] != -69)
	{
		map[signal] = map[signalA] << shiftNum;
	}
}

void HandleRShift(const std::string& signal, const std::string& signalA, int shiftNum, std::map<std::string, int>& map)
{
	if (map[signalA] != -69)
	{
		map[signal] = map[signalA] >> shiftNum;
	}
}

int main()
{
	std::ifstream file;
	file.open("input.txt");
	std::string line;
	std::map<std::string, int> wires;
	std::vector<std::string> vec;

	/* add all signals to map*/
	while (getline(file, line))
	{
		std::stringstream tempLine(line);
		std::string a, b, c, d, e;

		tempLine >> a >> b >> c >> d >> e;

		vec.assign({ a,b,c,d,e });

		GetSignal(vec, wires);


	}
	file.clear();
	file.seekg(0);


	for (int i = 0; i < 200; ++i)
	{
		/* attempt to calculate in a loop until A is found out */
		while (getline(file, line))
		{
			std::stringstream tempLine(line);
			std::string a, b, c, d, e;

			std::string gate;
			std::string signal;

			tempLine >> a >> b >> c >> d >> e;
			vec.assign({ a,b,c,d,e });

			/* get seperated variables */
			gate = GetGate(vec, wires);
			signal = GetSignal(vec, wires);


			/* handle logic */
			switch (GateToEnum(gate))
			{
			case NONE:
				HandleNoGate(a, signal, wires);
				break;
			case AND:
				HandleAnd(signal, a, c, wires);
				break;
			case OR:
				HandleOr(signal, a, c, wires);
				break;
			case NOT:
				HandleNot(signal, b, wires);
				break;
			case LSHIFT:
				HandleLShift(signal, a, std::stoi(c), wires);
				break;
			case RSHIFT:
				HandleRShift(signal, a, std::stoi(c), wires);
				break;
			default:
				break;
			}


		}



		file.clear();
		file.seekg(0);

	}


	return 0;
}
