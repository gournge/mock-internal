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
        // cout << "the following move has won!\n";
        // cout << pos << " : " << sign << "\n";


        grid.put(pos, ' ');
        return (sign == 'X') ? -1 : 1;
    }

    if (depth == 0) {
        // std::cout << "\n\n DEPTH LIMIT REACHED ! ! !\n";
        // cout << "\n";
        // grid.display();
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
            // if the cell is full
            if (grid.at(move) != ' ') continue;

            int e = evaluate(depth-1, grid, move, 'O');
            // cout << e << "\n";

            // if there is a chance for the opposite player
            // to achieve a certain win, assume he will go for it 
            if (e == 1) {
                // std::cout << "\n - - -\n";
                grid.put(pos, ' ');
                return 1;
            }
            best = (best > e) ? e : best;
        }
        grid.put(pos, ' ');
        return best;

    } else {
        int best = -2;
        for (int move : possible_moves) {
            // if the cell is full
            if (grid.at(move) != ' ') continue;

            int e = evaluate(depth-1, grid, move, 'X');
            // cout << e << "\n";

            if (e == -1) {
                // std::cout << "\n - - -\n";
                grid.put(pos, ' ');
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
        // value: 9  16  4 3 3 3
        vector<int> table = {9, 16, 4, 3, 3, 3, 1, 1};
        max_depth = table[size - 3];
    } else {
        max_depth = depth;
    }
    
    // if there is less than 60% of blank space, increase search depth
    if (grid.get_empty() < size*size * 3/5) max_depth += 3; 

    std::vector<Pos> lead_to_draw;
    auto possible_moves = grid.get_cell_check_order();
    for (auto move : possible_moves)
    {
        // if the cell is full
        if (grid.at(move) != ' ') continue;

        Pos m = grid.convert(move);

        // if the cell is outside the quarter board skip it
        // in the beginning the board is symmetric
        bool empty_board = grid.get_empty() == size*size;
        int quarter_board = (size % 2 == 0) ? size/2 : size/2 + 1; 
        bool outside_of_quarter = !(m.inrange(quarter_board));
        if (empty_board && outside_of_quarter) continue;
     
        int e = evaluate(max_depth, grid, move, sign);

        // cout << "Move: " << m.x << " " << m.y 
        //      << " evaluated at " << e << " " << "\n";

        if (e == optimal) return m;
        if (e == 0) lead_to_draw.push_back(m);
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

