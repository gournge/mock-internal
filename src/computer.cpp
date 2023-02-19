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
int evaluate(int depth, Grid &grid, const int pos, const char sign, int& count) {
    
    grid.put(pos, sign);

    if (grid.check(grid.convert(pos), sign)) { 
        count++;
        grid.put(pos, ' ');
        return (sign == 'X') ? -1 : 1;
    }

    if (depth == 0) {
        count++;
        grid.put(pos, ' ');
        return 0;
    }

    if (grid.get_empty() == 0) {
        count++;
        grid.put(pos, ' ');
        return 0;
    }

    const auto& possible_moves = grid.get_cell_check_order();
    
    if (sign == 'X') {
        // X position has been put. now it is O's turn.

        // every evaluation is now better than this value
        int best = -2;
        for (int move : possible_moves) {
            // if the cell is full
            if (grid.at(move) != ' ') continue;

            int e = evaluate(depth-1, grid, move, 'O', count);
            // cout << e << "\n";

            // if there is a chance for the opposite player
            // to achieve a certain win, assume he will go for it 
            if (e == 1) {
                // std::cout << "\n - - -\n";
                grid.put(pos, ' ');
                // cout << "evaluation: " << 1 << "\n"; 

                return 1;
            }
            // pick maximizing move
            if (best < e) best = e;
        }
        grid.put(pos, ' ');
        // cout << "evaluation: " << best << "\n"; 
        return best;

    } else {
        int best = 2;
        for (int move : possible_moves) {
            // if the cell is full
            if (grid.at(move) != ' ') continue;

            int e = evaluate(depth-1, grid, move, 'X', count);
            // cout << e << "\n";

            if (e == -1) {
                // std::cout << "\n - - -\n";
                grid.put(pos, ' ');
                // cout << "evaluation: " << -1 << "\n"; 
                return -1;
            }
            if (best > e) best = e;
        }
        grid.put(pos, ' ');
        // cout << "evaluation: " << best << "\n"; 
        return best;
    }
}

// depth by default -1
Pos find_best(Grid &grid, char sign, int depth) {

    int size = grid.get_size();
    int optimal = (sign == 'X') ? -1 : 1;

    // max_depth tested on evaluating first move
    int max_depth;

    if (grid.get_empty() >= size*size-1) {
        switch (size)
        {
        case 10:
            if (grid.at({4, 4}) == ' ') return {4, 4};
            else return {5, 5};

        case 9:
            if (grid.at({4, 4}) == ' ') return {4, 4};
            else return {5, 5};

        case 8:
            if (grid.at({4, 4}) == ' ') return {4, 4};
            else return {3, 3};

        case 7:
            if (grid.at({4, 4}) == ' ') return {4, 4};
            else return {3, 3};

        default:
            break;
        }
    }

    if (depth == -1) {
        //  size: 3  4   5 6 7 8 9 10
        // value: 9  16  
        vector<int> table = {9, 16, 3, 3, 3, 2, 2, 2};
        max_depth = table[size - 3];
    } else {
        max_depth = depth;
    }
    
    // if there is less than 60% of blank space, increase search depth
    if (grid.get_empty() < (size*size * 3/5)) max_depth += 1; 

    // how many leaves does the search function traversed
    int count = 0;

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

        int e = evaluate(max_depth, grid, move, sign, count);


        if (e == optimal) return m;
        if (e == 0) lead_to_draw.push_back(m);
    }

    cout << "The search function went through " << count << " scenarios.\n";

    // if no optimal move is found, return a random one
    srand((unsigned) time(NULL));

    // some moves lead to draw : pick the first ones, since they are at the center
    
    if (lead_to_draw.size() > 0) {
        vector<Pos> promising;

        for (Pos cand1 : find_promising(grid, sign)) {
            for (Pos cand2 : lead_to_draw) {
                if (cand1 == cand2) promising.push_back(cand1);
            }
        }

        int s = promising.size();
        if (s > 0) return promising[rand() % s];

        return lead_to_draw[0];
    }
    
    // every move leads to losing
    int random_losing_move =  possible_moves[rand() % possible_moves.size()];
    return grid.convert(random_losing_move);
}

// evoked only when the algorithm does not find any winning moves
vector<Pos> find_promising(Grid &grid, char sign) {

    int s = grid.get_size();
    // sign of the opponent
    char other = (sign == 'X') ? 'O' : 'X';

    // iterate through all cells and consider the ones with neighbors
    vector<Pos> candidates;
    for (int i = 0; i < s*s; i++) {
        Pos any_cell = grid.convert(i);
        if (grid.at(any_cell) != ' ') {
            for (Pos neighbor : find_neighbors(grid, sign, any_cell)) {
                if (grid.at(neighbor) == ' ') {
                    candidates.push_back(neighbor);
                }
            }
        }
    }

    // if it would create/block a line of three
    vector<Pos> good_candidates;
    // if it would create/block a line of four
    vector<Pos> very_good_candidates;

    for (Pos cand : candidates) {
        for (Pos neighbor : find_neighbors(grid, sign, cand)) {

            if (grid.at(neighbor) != ' ') {
                
                // neighbor of the neighbor in line
                Pos n_neighbor = {neighbor.x - (cand.x - neighbor.x), 
                                  neighbor.y - (cand.y - neighbor.y)};

                // discard if it comes out of the board
                if (!n_neighbor.inrange(grid.get_size()))
                    continue;

                // discard if they are different
                if (grid.at(n_neighbor) != grid.at(neighbor)) 
                    continue;
                good_candidates.push_back(cand);

                // neighbor of n_neighbor in line
                Pos n_n_neighbor = {n_neighbor.x - (neighbor.x - n_neighbor.x), 
                                    n_neighbor.y - (neighbor.y - n_neighbor.y)};

                // if it comes out of the board
                if (!n_n_neighbor.inrange(grid.get_size()))
                    continue;
                very_good_candidates.push_back(cand);
            }
        }
    }

    if (very_good_candidates.size() > 0) return very_good_candidates;
    if (good_candidates.size() > 0) return good_candidates;
    return candidates;
}

vector<Pos> find_neighbors(Grid &grid, char sign, Pos cell) {

    vector<Pos> temp;
    int x = cell.x, y = cell.y;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if ((i == j) && (j == 0)) continue;
            
            Pos neighbor{x+i, y+j};
            if (!neighbor.inrange(grid.get_size())) continue; 

            temp.push_back({x+i, y+j});
        }
    }

    return temp;
}