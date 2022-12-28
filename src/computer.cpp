#include <iostream>
#include <cstdlib>
#include <time.h>
#include "computer.hpp"

using std::cout;
using std::vector;


// recursive evaluation that assumes both players play optimally.
// evaluation of putting sign on position p
// > +1 if 'O' wins 
// > -1 if 'X' wins
// > 0 for draw
int evaluate(int depth, Grid &grid, const Pos p, const char sign) {

    // cout << "\n\n";
    // grid.display();
    // cout << p.x << " " << p.y << " : " << sign << "\n";
    // cout << "empty: " << grid.getempty() << "\n";
 
    grid.put(p, sign);

    if (grid.check(p, sign)) { 
        // std::cout << "\n - - -\n";

        // grid.display();
        // cout << "the following move has won!\n";`1É
        // cout << p.x << " " << p.y << " : " << sign << "\n";


        grid.put(p, ' ');
        return (sign == 'X') ? -1 : 1;
    }

    if (depth == 0) {
        // std::cout << "\n\n DEPTH LIMIT REACHED ! ! !\n";
        grid.put(p, ' ');
        return 0;
    }

    if (grid.get_empty() == 0) {
        // std::cout << "\n\n THE BOARD IS FULL ! ! !\n\n";

        // grid.display();

        grid.put(p, ' ');
        return 0;
    }

    auto possible_moves = grid.get_cell_importance();
    
    if (sign == 'X') {
        int best = 2;
        for (Pos move : options(grid)) {

            int e = evaluate(depth-1, grid, move, 'O');
            // cout << e << "\n";

            // if there is a chance for the opposite player
            // to achieve a certain win, he will go for it 
            if (e == 1) {
                grid.put(p, ' ');
                // std::cout << "\n - - -\n";
                return 1;
            }
            best = (best > e) ? e : best;
        }
        grid.put(p, ' ');
        return best;

    } else {
        int best = -2;
        for (Pos move : options(grid)) {

            int e = evaluate(depth-1, grid, move, 'X');
            // cout << e << "\n";

            if (e == -1) {
                grid.put(p, ' ');
                // std::cout << "\n - - -\n";
                return -1;
            }
            best = (best < e) ? e : best;
        }
        grid.put(p, ' ');
        return best;
    }
}

Pos find_best(Grid &grid, char sign) {

    int size = grid.get_size();
    int optimal = (sign == 'X') ? -1 : 1;

    std::vector<Pos> lead_to_draw;

    auto opts = options(grid);

    // max_depth tested on evaluating first move

    //  size: 3  4   5 6 7 8 9 10
    // value: 9  16  4 3 
    int table[] = {9, 16, 4, 3};
    const int max_depth = table[size - 3];


    for (auto move : opts)
    {
        int e = evaluate(max_depth, grid, move, sign);

        // cout << "Move: " << move.x << " " << move.y 
        //      << " evaluated at " << e << " " << "\n";

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

