#include <iostream>
#include <deque>
#include <algorithm>
using namespace std;

constexpr unsigned STEPS = 12459852;

enum State
{
	A,
	B,
	C,
	D,
	E,
	F
};

void StateA(bool&, deque<bool>&, int&, State&);
void StateB(bool&, deque<bool>&, int&, State&);
void StateC(bool&, deque<bool>&, int&, State&);
void StateD(bool&, deque<bool>&, int&, State&);
void StateE(bool&, deque<bool>&, int&, State&);
void StateF(bool&, deque<bool>&, int&, State&);


void IncreaseDeque(deque<bool>& tape, int& idx)
{
	if ((idx + 1) > tape.size() - 1)
	{
		tape.push_back(0);
		++idx;
	}
	else
	{
		++idx;
	}

}

void DecrementDeque(deque<bool>& tape, int& idx)
{
	if ((idx - 1) < 0)
	{
		tape.push_front(0);
		idx = 0;
	}
	else
	{
		--idx;
	}

}

void StateA(bool& num, deque<bool>& tape, int& idx, State& state)
{
	if (num == 0)
	{
		num = 1;
		IncreaseDeque(tape, idx);
		state = B;

	}
	else if (num == 1)
	{
		num = 1;
		DecrementDeque(tape, idx);
		state = E;
	}



}
void StateB(bool& num, deque<bool>& tape, int& idx, State& state)
{

	if (num == 0)
	{
		num = 1;
		IncreaseDeque(tape, idx);
		state = C;
	}
	else if (num == 1)
	{
		num = 1;
		IncreaseDeque(tape, idx);
		state = F;

	}


}
void StateC(bool& num, deque<bool>& tape, int& idx, State& state)
{

	if (num == 0)
	{
		num = 1;
		DecrementDeque(tape, idx);
		state = D;
	}
	else if (num == 1)
	{
		num = 0;
		IncreaseDeque(tape, idx);
		state = B;
	}


}
void StateD(bool& num, deque<bool>& tape, int& idx, State& state)
{


	if (num == 0)
	{
		num = 1;
		IncreaseDeque(tape, idx);
		state = E;
	}
	else if (num == 1)
	{
		num = 0;
		DecrementDeque(tape, idx);
		state = C;
	}


}
void StateE(bool& num, deque<bool>& tape, int& idx, State& state)
{

	if (num == 0)
	{
		num = 1;
		DecrementDeque(tape, idx);
		state = A;
	}
	else if (num == 1)
	{
		num = 0;
		IncreaseDeque(tape, idx);
		state = D;
	}


}
void StateF(bool& num, deque<bool>& tape, int &idx, State& state)
{

	if (num == 0)
	{
		num = 1;
		IncreaseDeque(tape, idx);
		state = A;
	}
	else if (num == 1)
	{
		num = 1;
		IncreaseDeque(tape, idx);
		state = C;
	}



}

int main()
{
	deque<bool> tape = { 0 };
	State currState = A;
	int idx = 0;
	int currStep = 0;
	while (currStep < STEPS)
	{
		switch (currState)
		{
		case A: StateA(tape[idx], tape, idx, currState); break;
		case B:	StateB(tape[idx], tape, idx, currState); break;
		case C:	StateC(tape[idx], tape, idx, currState); break;
		case D:	StateD(tape[idx], tape, idx, currState); break;
		case E:	StateE(tape[idx], tape, idx, currState); break;
		case F:	StateF(tape[idx], tape, idx, currState); break;
		}

		++currStep;
	}


	int cnt = count(tape.begin(), tape.end(), 1);


	cout << cnt;
	return 0;
}