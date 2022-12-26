#include <iostream>
#include <cstdlib>
#include <time.h>
#include "computer.hpp"

using std::cout;
using std::vector;

vector<Pos> options(const Grid &grid)
{
    vector<Pos> opts;

    for (int x = 0; x < grid.getsize(); x++)
    {
        for (int y = 0; y < grid.getsize(); y++)
        {
            Pos p{x, y};
            if (grid.at(p) == ' ') opts.push_back(p);
        }
    }

    return opts;
}

// recursive evaluation that assumes both players play optimally.
// evaluation of putting sign on position p
// > +1 if 'O' wins 
// > -1 if 'X' wins
// > 0 for draw
int evaluate(int depth, Grid &grid, Pos p, char sign) {

    cout << p.x << " " << p.y << " " << sign << "\n";

    // 
    if (depth == 0) {
        std::cout << "\n\n DEPTH LIMIT REACHED ! ! !\n";
        return 0;
    }

    grid.put(p, sign);

    if (grid.check(p, sign)) { 
        std::cout << " - - -\n";
        grid.put(p, ' ');
        return (sign == 'X') ? -1 : 1;
    }

    if (grid.empty == 0) {
        std::cout << "\n\n THE BOARD IS FULL ! ! !\n\n";
        grid.put(p, ' ');
        return 0;
    }

    if (sign == 'X') {
        int best = 2;
        for (Pos move : options(grid)) {

            int e = evaluate(depth-1, grid, move, 'O');

            if (e == -1) {
                grid.put(p, ' ');
                std::cout << " - - -\n";
                return -1;
            }
            best = (best > e) ? e : best;
        }
        grid.put(p, ' ');
        return best;

    } else {
        int best = -2;
        for (Pos move : options(grid)) {

            int e = evaluate(depth-1, grid, move, 'X');

            if (e == 1) {
                grid.put(p, ' ');
                std::cout << " - - -\n";
                return 1;
            }
            best = (best < e) ? e : best;
        }
        grid.put(p, ' ');
        return best;
    }
}

Pos find_best(Grid &grid, char sign) {
    int optimal = (sign == 'X') ? -1 : 1;

    std::vector<Pos> lead_to_draw;

    auto opts = options(grid);

    const int max_depth = grid.getsize()

    for (auto move : opts)
    {
        int e = evaluate(50, grid, move, sign);

        cout << e << " " << move.x << " " << move.y << "\n";

        if (e == optimal) return move;
        if (e == 0) lead_to_draw.push_back(move);
    }

    // if no optimal move is found, return a random one
    srand((unsigned) time(NULL));

    // some moves lead to draw
    int s = lead_to_draw.size();
    if (s > 0) return lead_to_draw[rand() % s];

    // every move leads to losing
    return opts[rand() % opts.size()];
}

