#pragma once
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