#include <iostream>
#include <limits>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <sstream>
#include <regex>
#include <tuple>
#include <limits>
#include <iomanip>

using namespace std;
const int list_max = 256;

template <typename T, typename Iterator>
class CyclicIterator : public std::iterator <std::bidirectional_iterator_tag, T, ptrdiff_t> {
    int   cursor;
    int   length;
    Iterator begin;

public:
    CyclicIterator(const Iterator& i, const Iterator& j) : cursor(0), length(std::distance(i, j)), begin(i) {}

    bool operator == (const CyclicIterator& x) const {
        return cursor == x.cursor;
    }

    bool operator != (const CyclicIterator& x) const {
        return !(*this == x);
    }

    T& operator*() const {
        int wrapped = cursor;
        while (wrapped < 0) wrapped += length;
        while (wrapped >= length) wrapped -= length;

        return *(begin + wrapped);
    }

    CyclicIterator& operator += (const int i) {
        cursor += i;
        return *this;
    }

    CyclicIterator& operator-(const int i) {
        cursor -= i;
        return *this;
    }

    CyclicIterator& operator++() {
        ++cursor;
        return *this;
    }

    CyclicIterator operator++(int) {
        CyclicIterator ring = *this;
        ++*this;
        return ring;
    }

    CyclicIterator& operator--() {
        --cursor;
        return *this;
    }

    CyclicIterator operator--(int) {
        CyclicIterator ring = *this;
        --*this;
        return ring;
    }
};

template<class T>
void knothash(T input, vector<unsigned short>& v, int& shift, int& zero_index) {
    for (unsigned short i : input) {
        CyclicIterator<unsigned short, vector<unsigned short>::iterator> bcycle(v.begin(), v.end());
        bcycle += zero_index;

        CyclicIterator<unsigned short, vector<unsigned short>::iterator> ecycle(v.begin(), v.end());
        ecycle += zero_index + i;

        reverse(bcycle, ecycle);

        zero_index += i + shift;
        while (zero_index >= list_max) zero_index -= list_max;

        ++shift;
        while (shift >= list_max) shift -= list_max;
    }
}

int main() {
    string input = "flqrgnkx-2";

    vector<unsigned short> suffix{ 17, 31, 73, 47, 23 };
    vector<unsigned short> v(list_max);
    for (unsigned short i = 0; i < list_max; ++i) v[i] = i;

    int shift = 0;
    int zero_index = 0;
    for (int j = 0; j < 64; ++j) {
        knothash(input, v, shift, zero_index);
        knothash(suffix, v, shift, zero_index);
    }

    for (int i = 0; i < 16; ++i) {
        unsigned short densehash = 0;
        for (int j = 0; j < 16; ++j) {
            densehash ^= v[i * 16 + j];
        }
        cout << setfill('0') << setw(2) << hex << densehash;
    }
    cout << '\n';
}