#pragma once

#include <vector>
#include <map>

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
        void put(Pos m, char c);

        void display() const;
        bool check(Pos m, char sign) const;

        std::vector<int> get_neighbors(const int p);
        std::map<int, int> get_cell_importance();        

    private:
        std::vector<char> data;
        int size;
        int empty;

        std::vector<Pos> convert_table;
 
        // keys refer to converted positions. 
        // when a sign is put its neigbors get incremented by size since initially 
        // lowest value is 1 and highest is size-1.
        // in that way said neighbors get pushed to the front
        std::map<int, int> cell_importance;
        std::map<int, int> cell_importance_base;
};

