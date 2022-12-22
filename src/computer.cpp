#include <cstdlib>
#include <time.h>
#include "computer.hpp"

vector<Pos> options(const Grid &grid)
{
    vector<Pos> opts;

    for (int x = 0; x < grid.size; x++)
    {
        for (int y = 0; y < grid.size; y++)
        {
            Pos p{x, y};
            if (grid.at(p) == ' ') opts.push_back(p);
        }
    }

    return opts;
}

// recursive evaluation that assumes both players play optimally.
// + 1 if 'O' wins 
// - 1 if 'X' wins
//   0 for draw
int evaluate(const Grid &grid, Pos p) {

    return 2;
}

Pos find_best(Grid &grid, char sign) {
    int optimal = (sign == 'X') ? -1 : 1;

    auto opts = options(grid);
    for (auto move : opts)
    {
        grid.put(move, sign);
        int e = evaluate(grid, move);
        grid.put(move, ' ');

        if (e == optimal) return move;
    }

    // if no optimal move is found, return a random one 
    srand((unsigned) time(NULL));
    return opts[rand() % opts.size()];
}