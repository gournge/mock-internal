#include <iostream>
#include <cstdlib>
#include <time.h>
#include "computer.hpp"

using std::cout;

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
// evaluation of putting sign on position p
// > +1 if 'O' wins 
// > -1 if 'X' wins
// > 0 for draw
int evaluate(Grid &grid, Pos p, char sign) {

    cout << p.x << " " << p.y << " " << sign << "\n";

    grid.put(p, sign);

    if (grid.check(p, sign)) { 
        std::cout << " - - -\n";
        grid.put(p, ' ');
        return (sign == 'X') ? -1 : 1;
    }

    if (grid.empty == 0) {
        std::cout << " DEPTH LIMIT REACHED ! ! !\n";
        grid.put(p, ' ');
        return 0;
    }

    if (sign == 'X') {
        int best = 2;
        for (Pos move : options(grid)) {

            int e = evaluate(grid, move, 'O');

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

            int e = evaluate(grid, move, 'X');

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


    for (auto move : opts)
    {
        int e = evaluate(grid, move, sign);

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