#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <stdexcept>
#include "utils.hpp"

using std::vector;
using std::cout;

vector<int> spiral_from_middle_decreasing(const int size) {

    if (size == 3) return {4, 3, 6, 7, 8, 5, 2, 1, 0};

    vector<vector<int>> table(size, vector<int>(size, 0));

    // order of checking cells
    // i-th element means position i has importance i
    vector<int> spiral_converted;

    int dir_count = 0;
    int dirsx[4] = {0, 1, 0, -1};
    int dirsy[4] = {1, 0, -1, 0};
    int x = 0,   y = 0;
    int dx = 0, dy = 0;
    
    // begins at the top left corner ends in the middle
    for (int i = 0; i <= size*size-1; i++) { 
        spiral_converted.push_back(y*size + x);

        table[x][y] = size*size - i;

        dx = dirsx[dir_count%4];
        dy = dirsy[dir_count%4];
        x += dx; y += dy;

        if ( ((x == 0 || x == size-1) && 
              (y == 0 || y == size-1)) 
           || (table[x+dx][y+dy]))
        { dir_count++; }
    }

    // begins in the middle ends at top left corner
    std::reverse(spiral_converted.begin(), spiral_converted.end());
    return spiral_converted;
}

bool Pos::inrange(int size) const {
    return (0 <= x) && (x < size) &&
           (0 <= y) && (y < size);
}

bool operator==(const Pos& p1, const Pos& p2) {
    return (p1.x == p2.x) && (p1.y == p2.y);
}


Grid::Grid() { }

// constructor -> computionally expensive work done only once 
Grid::Grid(int s) {
    size = s;
    data = vector<char>(size * size, ' ');
    empty = size * size;


    vector<Pos> temp;
    for (int y = 0; y < size; y++)
    {
        for (int x = 0; x < size; x++)
        {
            temp.push_back({x, y});
        }
    }
    convert_table = temp;

    // highest values in the middle, declines to sides
    cell_check_order = spiral_from_middle_decreasing(size);
}

int Grid::get_empty() const {
    return empty;
}

Pos Grid::convert(int n) const {
    if ((n < 0) || (n >= size*size)) 
        throw std::out_of_range("Grid::convert; Indexing grid out of range : int type indexing");
    return convert_table[n];
}

int Grid::convert(Pos p) const {
    if (!p.inrange(size)) 
        throw std::out_of_range("Grid::convert; Indexing grid out of range : Pos type indexing");
    return p.y * size + p.x;
}

char Grid::at(Pos p) const {
    if (!p.inrange(size)) {
        cout << "what?\n";
        throw std::out_of_range("Grid::at; Indexing grid out of range : Pos type indexing");
    }
    // contents at position (x, y)
    return data[convert(p)];
}

char Grid::at(int n) const {
    if ((n < 0) || (n >= size*size)) 
        throw std::out_of_range("Grid::at; Indexing grid out of range : int type indexing");
    return data[n];
}

void Grid::put(int p, char c) {

    char before = at(p);

    // if the action fills the position 
    if ((before == ' ') && (c != ' ')) {
        empty--;
    }

    // if the action empties the position  
    if ((before != ' ') && (c == ' ')) {
        empty++;
    }

    // put char c on position p
    data[p] = c;
}

void Grid::put(Pos p, char c) {

    int integer_pos = convert(p);

    char before = at(p);

    // if the action fills the position 
    if ((before == ' ') && (c != ' ')) {
        empty--;
    }

    // if the action empties the position 
    if ((before != ' ') && (c == ' ')) {
        empty++;
    }

    // put char c on position (x, y)
    data[integer_pos] = c;
}

int Grid::get_size() const {
    return size;
}

std::vector<int> Grid::get_cell_check_order() {
    return cell_check_order;
}

void Grid::display() const
{

    cout << "  ";
    for (int x = 0; x < size; x++)
    {
        cout << x << " ";
    }
    cout << "\n";

    for (int y = 0; y < size - 1; y++)
    {
        cout << y << " ";
        for (int x = 0; x < size - 1; x++)
        {
            cout << at({x, y}) << '|';
        }
        cout << at({size - 1, y}) << '\n';
        
        cout << "  "; 
        for (int x = 0; x < 2 * size - 1; x++)
        {
            cout << '-';
        }
        cout << '\n';
    }
    cout << size-1 << " ";
    for (int x = 0; x < size - 1; x++)
    {
        cout << at({x, size - 1}) << '|';
    }
    cout << at({size - 1, size - 1}) << "\n";
}

bool Grid::check(Pos p, char sign) const 
{
    int to_win = (size > 4) ? 5 : 3;
    int init_val = (at(p) == ' ') ? 1 : 0;

    // too little to win
    if (get_empty() < 2*(to_win-1)) return false;

    // perpendicular lines check
    for (int i = 0; i < to_win; i++)
    {
        int ver{init_val}, hor{init_val}, diag1{init_val}, diag2{init_val};
        for (int j = 0; j < to_win; j++)
        {

            int xnew = p.x - i + j, ynew = p.y - i + j;
            int xdiag = p.x - i + j, ydiag = p.y + i - j;

            // count if belongs to a certain line
            if (Pos{xnew, 0}.inrange(size) &&
                at({xnew, p.y}) == sign)
                ver++;

            if (Pos{0, ynew}.inrange(size) &&
                at({p.x, ynew}) == sign)
                hor++;

            if (Pos{xnew, ynew}.inrange(size) &&
                at({xnew, ynew}) == sign)
                diag1++;

            if (Pos{xdiag, ydiag}.inrange(size) &&
                at({xdiag, ydiag}) == sign)
                diag2++;
        }
        // cout << "- - -\n";
        if ((ver >= to_win) || (hor >= to_win) ||
            (diag1 >= to_win) || (diag2 >= to_win))
            return 1;
    }
    return 0;
}