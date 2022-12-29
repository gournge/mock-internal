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
int evaluate(int depth, Grid &grid, const int pos, const char sign) {

    // cout << "\n\n";
    // grid.display();
    // cout << p.x << " " << p.y << " : " << sign << "\n";
    // cout << "empty: " << grid.getempty() << "\n";
 
    grid.put(pos, sign);

    if (grid.check(grid.convert(pos), sign)) { 
        // std::cout << "\n - - -\n";

        // grid.display();
        // cout << "the following move has won!\n";`1É
        // cout << p.x << " " << p.y << " : " << sign << "\n";


        grid.put(pos, ' ');
        return (sign == 'X') ? -1 : 1;
    }

    if (depth == 0) {
        // std::cout << "\n\n DEPTH LIMIT REACHED ! ! !\n";
        grid.put(pos, ' ');
        return 0;
    }

    if (grid.get_empty() == 0) {
        // std::cout << "\n\n THE BOARD IS FULL ! ! !\n\n";

        // grid.display();

        grid.put(pos, ' ');
        return 0;
    }

    auto possible_moves = grid.get_cell_check_order();
    
    if (sign == 'X') {
        int best = 2;
        for (int move : possible_moves) {

            int e = evaluate(depth-1, grid, move, 'O');
            // cout << e << "\n";

            // if there is a chance for the opposite player
            // to achieve a certain win, assume he will go for it 
            if (e == 1) {
                grid.put(pos, ' ');
                // std::cout << "\n - - -\n";
                return 1;
            }
            best = (best > e) ? e : best;
        }
        grid.put(pos, ' ');
        return best;

    } else {
        int best = -2;
        for (int move : possible_moves) {

            int e = evaluate(depth-1, grid, move, 'X');
            // cout << e << "\n";

            if (e == -1) {
                grid.put(pos, ' ');
                // std::cout << "\n - - -\n";
                return -1;
            }
            best = (best < e) ? e : best;
        }
        grid.put(pos, ' ');
        return best;
    }
}

// depth by default -1
Pos find_best(Grid &grid, char sign, int depth) {

    int size = grid.get_size();
    int optimal = (sign == 'X') ? -1 : 1;

    // max_depth tested on evaluating first move
    int max_depth;

    if (depth == -1) {
        //  size: 3  4   5 6 7 8 9 10
        // value: 9  16  4 3 
        int table[] = {9, 16, 4, 3, 3, 3};
        max_depth = table[size - 3];
    } else {
        max_depth = depth;
    }
    
    std::vector<Pos> lead_to_draw;
    auto possible_moves = grid.get_cell_check_order();
    for (auto move : possible_moves)
    {
        int e = evaluate(max_depth, grid, move, sign);

        Pos m = grid.convert(move);

        // cout << "Move: " << m.x << " " << m.y 
        //      << " evaluated at " << e << " " << "\n";

        if (e == optimal) return grid.convert(move);
        if (e == 0) lead_to_draw.push_back(grid.convert(move));
    }

    // if no optimal move is found, return a random one
    srand((unsigned) time(NULL));

    // some moves lead to draw
    int s = lead_to_draw.size();
    if (s > 0) return lead_to_draw[rand() % s];

    // every move leads to losing
    int random_losing_move =  possible_moves[rand() % possible_moves.size()];
    return grid.convert(random_losing_move);
}

