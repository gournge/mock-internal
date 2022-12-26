#pragma once

#include <vector>

struct Pos {
    int x, y;

    // if the vector (x, y) is contained
    // in the square (0, 0), (size-1, size-1)
    bool inrange(int size); 
};

class Grid {
    public:
        Grid();
        Grid(int s);

        int getempty() const; // the amount of empty cells
        int getsize() const;

        char at(Pos m) const;
        void put(Pos m, char c);

        void display() const;
        bool check(Pos m, char sign) const;

    private:
        std::vector<char> data;
        int size;
        int empty;

        // useful 
        // std::vector<Pos> cell_importance;
};

