#include <iostream>
#include <stdexcept>
#include "utils.hpp"

using namespace std;

bool Pos::inrange(int size) {
    return (0 <= x) && (x < size) &&
           (0 <= y) && (y < size);
}

Grid::Grid() { }

Grid::Grid(int s) {
    size = s;
    data = vector<char>(size * size, ' ');
    empty = size * size;
}

int Grid::getempty() const {
    return empty;
}

char Grid::at(Pos p) const {
    // contents at position (x, y)
    return data[p.y * size + p.x];
}

void Grid::put(Pos p, char c) {

    if (!p.inrange(size)) throw std::out_of_range("Indexing grid out of range");

    char before = at(p);

    // put char c on position (x, y)
    data[p.y * size + p.x] = c;

    if ((before == ' ') && (c != ' ')) empty--;
    if ((before != ' ') && (c == ' ')) empty++;
}

int Grid::getsize() const {
    return size;
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
    cout << at({size - 1, size - 1}) << "\n" << endl;
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
            {
                diag2++;
            //     cout << xdiag << " "  << ydiag 
            //   << " " << at({xdiag, ydiag}) << "\n";

            }

            // cout << xdiag << " "  << ydiag << " " << Pos{xdiag, ydiag}.inrange(size) << "\n";

            
            // if (Pos{p.x - i - j, ynew}.inrange(size))
            // cout << p.x - i - j << " "  << ynew << " " << at({p.x - i - j, ynew}) << "\n";
            

            // cout << ver << " " << hor << " ";
            // cout << "\n" << i << " " << j << "\n"
            //         << diag1 << " " << diag2 << "\n";
            // cout << to_win << "\n";
            // cout << " - - - \n";
        }
        // cout << "- - -\n";
        if ((ver >= to_win) || (hor >= to_win) ||
            (diag1 >= to_win) || (diag2 >= to_win))
            return 1;
    }

    // // check rows
    // for (int shift = 0; shift < to_win; shift++)
    // {
    //     for (int index = 0; index < to_win; index++)
    //     {
    //         Pos new_pos {p.x - shift + index, p.y - shift + index};

    //         if (not new_pos.inrange(size))
    //             break;

            
    //     }
    // }
    

    return 0;
}
