#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include "utils.hpp"

using std::vector;
using std::cout;

vector<int> Grid::get_neighbors(const int integer_pos) {
    vector<int> temp; 

    const int residue = integer_pos % size;

    // refer to this example:
    // 0|1|2
    // -----
    // 3|4|5
    // -----
    // 6|7|8

    {
    // true if coords are valid
    bool top = integer_pos > size-1;
    bool bottom = integer_pos < size*(size-1);
    bool right = residue != size-1;
    bool left = residue != 0;

    if(top) 
        temp.push_back(integer_pos - size);

    if(bottom) 
        temp.push_back(integer_pos + size);

    if(left) 
        temp.push_back(integer_pos - 1);

    if(right) 
        temp.push_back(integer_pos + 1);

    if(top && right)
        temp.push_back(integer_pos - size + 1);

    if(top && left)
        temp.push_back(integer_pos - size - 1);

    if(bottom && right)
        temp.push_back(integer_pos + size + 1);

    if(bottom && left)
        temp.push_back(integer_pos + size - 1);
    }

    return temp;
}


bool Pos::inrange(int size) const {
    return (0 <= x) && (x < size) &&
           (0 <= y) && (y < size);
}

Grid::Grid() { }

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
    for (auto position_on_board : convert_table) {
        int sum = abs(2*position_on_board.x - size + 1) + 
                  abs(2*position_on_board.y - size + 1);
        cell_importance_base[convert(position_on_board)] = size - sum/2;   
    }
    cell_importance = cell_importance_base;

}

int Grid::get_empty() const {
    return empty;
}

Pos Grid::convert(int n) const {
    if ((n < 0) || (n >= size)) 
        throw std::out_of_range("Indexing grid out of range");
    return convert_table[n];
}

int Grid::convert(Pos p) const {
    if (!p.inrange(size)) 
        throw std::out_of_range("Indexing grid out of range");
    return p.y * size + p.x;
}

char Grid::at(Pos p) const {
    // contents at position (x, y)
    return data[convert(p)];
}

void Grid::put(Pos p, char c) {

    int integer_pos = convert(p);

    char before = at(p);

    auto neighbors = get_neighbors(integer_pos);
    if ((before == ' ') && (c != ' ')) {
        cell_importance.erase(integer_pos);
        for (auto cell : neighbors)
            cell_importance[cell] += size;
        empty--;
    }
    if ((before != ' ') && (c == ' ')) {
        cell_importance[integer_pos] = cell_importance_base[integer_pos];
        cell_importance[integer_pos] += size * neighbors.size();
        empty++;
    }

    // put char c on position (x, y)
    data[integer_pos] = c;
}

int Grid::get_size() const {
    return size;
}

std::map<int, int> Grid::get_cell_importance() {
    return cell_importance;
}

void Grid::display() const
{
    for (int y = 0; y < size - 1; y++)
    {
        for (int x = 0; x < size - 1; x++)
        {
            cout << at({x, y}) << '|';
        }
        cout << at({size - 1, y}) << '\n';
        for (int x = 0; x < 2 * size - 1; x++)
        {
            cout << '-';
        }
        cout << '\n';
    }
    for (int x = 0; x < size - 1; x++)
    {
        cout << at({x, size - 1}) << '|';
    }
    cout << at({size - 1, size - 1}) << "\n" << std::endl;
}

bool Grid::check(Pos p, char sign) const 
{
    int to_win = (size > 4) ? 5 : 3;
    int init_val = (at(p) == ' ') ? 1 : 0;

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
