#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <algorithm>
using namespace std;

#pragma region PART1

bool PreqsSatisfied(const map<char, set<char>>& steps, const string& done, char step)
{
	for (char pre : steps.at(step))
	{
		if (done.find(pre) == string::npos)
			return false;
	}

	return true;
}


void DFS(const map<char, set<char>>& steps, string& result, int counter) 
{
	if (result.size() == counter) { return; }

	for (const auto& [step, prereqs] : steps)
	{
		if (result.find(step) != string::npos) continue;

		if (PreqsSatisfied(steps, result, step))
		{
			result.push_back(step);
			DFS(steps, result, counter);

			if (result.size() == counter) return;
			result.pop_back();
		}


	}





};
#pragma endregion



#pragma region PART2

struct Worker
{
	char step = 0;
	int timeLeft = 0;

};
int stepDuration(char step)
{
	return 60 + (step - 'A') + 1;
}
void Simulate(const map<char, set<char>>& steps, string& result, int numWorkers)
{
	map<char, std::set<char>> stepsCopy = steps; // mutable copy
	string done;
	vector<Worker> workers(numWorkers);
	int time = 0;
	while (done.size() < steps.size())
	{
		for (auto& worker : workers)
		{
			// if worker is available, process a step
			if (worker.step == 0)
			{
				for (const auto& [step, prereqs] : stepsCopy)
				{
					// if prereqs satisfied
					if (done.find(step) == string::npos &&
						worker.step == 0 &&
						all_of(prereqs.begin(), prereqs.end(), [&](char p) { return done.find(p) != string::npos; }))
					{
						bool assigned = false;

						// check if workers not assigned
						for (const auto& w : workers)
						{
							if (w.step == step) assigned = true;
						}

						if (!assigned)
						{
							worker.step = step;
							worker.timeLeft = stepDuration(step);
							break;
						}

					}

				}
			}


		}
		++time;

		for (auto& worker : workers)
		{
			if (worker.step != 0)
			{
				worker.timeLeft--;
				if (worker.timeLeft == 0)
				{
					done.push_back(worker.step);
					worker.step = 0;
				}
			}
		}

	}
	


	cout << time;
}

#pragma endregion

int main()
{
	fstream file("input.txt");
	string line;
	map<char, set<char>> steps;
	string result;

	while (getline(file, line))
	{
		steps[line[36]].insert(line[5]);
		steps[line[5]];

	}
	//DFS(steps, result, steps.size());
	Simulate(steps, result, 5);

	//cout << result;


	return 0;
}

