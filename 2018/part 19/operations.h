#pragma once
#include <vector>
using namespace std;

void addr(vector<int>& reg, int A, int B, int C)
{
    reg[C] = reg[A] + reg[B];
}

void addi(vector<int>& reg, int A, int B, int C) 
{
    reg[C] = reg[A] + B;
}

void mulr(vector<int>& reg, int A, int B, int C) 
{
    reg[C] = reg[A] * reg[B];
}

void muli(vector<int>& reg, int A, int B, int C)
{
    reg[C] = reg[A] * B;
}

void banr(vector<int>& reg, int A, int B, int C) 
{
    reg[C] = reg[A] & reg[B];
}

void bani(vector<int>& reg, int A, int B, int C)
{
    reg[C] = reg[A] & B;
}

void borr(vector<int>& reg, int A, int B, int C) 
{
    reg[C] = reg[A] | reg[B];
}

void bori(vector<int>& reg, int A, int B, int C) 
{
    reg[C] = reg[A] | B;
}

void setr(vector<int>& reg, int A, int B, int C) 
{
    reg[C] = reg[A];
}

void seti(vector<int>& reg, int A, int B, int C) 
{
    reg[C] = A;
}

void gtir(vector<int>& reg, int A, int B, int C) 
{
    reg[C] = (A > reg[B]) ? 1 : 0;
}

void gtri(vector<int>& reg, int A, int B, int C) 
{
    reg[C] = (reg[A] > B) ? 1 : 0;
}

void gtrr(vector<int>& reg, int A, int B, int C)
{
    reg[C] = (reg[A] > reg[B]) ? 1 : 0;
}

void eqir(vector<int>& reg, int A, int B, int C) 
{
    reg[C] = (A == reg[B]) ? 1 : 0;
}

void eqri(vector<int>& reg, int A, int B, int C) 
{
    reg[C] = (reg[A] == B) ? 1 : 0;
}

void eqrr(vector<int>& reg, int A, int B, int C) 
{
    reg[C] = (reg[A] == reg[B]) ? 1 : 0;
}