#pragma once

#include <vector>
using namespace std;

struct Pos {
    int x;
    int y;
    bool inrange(int size);
};

struct Grid {
    vector<char> data;
    int size;

    Grid();
    Grid(int s);

    char at(Pos m) const;
    void put(Pos m, char c);

    void display();
    bool check(Pos m, char sign);
};

