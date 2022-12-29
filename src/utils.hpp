#pragma once

#include <vector>
#include <map>

std::vector<int> spiral_from_middle_decreasing(const int size);

struct Pos {
    int x, y;

    // if the vector (x, y) is contained
    // in the square (0, 0), (size-1, size-1)
    bool inrange(int size) const; 
};

class Grid {
    public:
        Grid();
        Grid(int s);

        int get_empty() const; // the amount of empty cells
        int get_size() const;

        // 0|1|2
        // -----
        // 3|4|5
        // -----
        // 6|7|8
        // convert as in example above 

        Pos convert(int) const;
        int convert(Pos) const;

        char at(Pos m) const;
        char at(int m) const;
        void put(Pos m, char c);
        void put(int m, char c);

        void display() const;
        bool check(Pos m, char sign) const;

        std::vector<int> get_cell_check_order();        

    private:
        std::vector<char> data;
        int size;
        int empty;

        std::vector<Pos> convert_table;

        // describes importance of the cells
        // first the cells from the middle are checked etc.
        std::vector<int> cell_check_order;
};

