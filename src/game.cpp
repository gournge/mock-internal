#include <iostream>
#include <cstdlib>
#include <time.h>
#include "game.hpp"
#include "utils.hpp"
#include "computer.hpp"

using namespace std;

#define ASK(IN, OUT) {cout << OUT; cin >> IN; cout << "\n";}

Game::Game() {

    do {
        ASK(size, "Enter the size of the TicTacToe grid: (between 3 and 10) ");
    } while ((size < 3) || (size > 10));

    ASK(with_computer, "Do you want to play with a computer? (0/1) ");

    if (with_computer) {
        name1 = "Computer";
        do {
        ASK(name2, "What is the player's 1 name? ");
        } while (name1 == name2);
    } else {
        ASK(name1, "What is player's 1 name? ");
        do {
        ASK(name2, "What is player's 2 name? "); 
        } while (name1 == name2);
    } 


    // if with_computer then name1 is "Computer"
    // and name2 is not

    // randomly changing the order of playing; always name1, name2
    srand((unsigned) time(NULL));
    bool should_swap_order = rand() % 2;
    if (should_swap_order) swap(name1, name2); // the contents of

    srand((unsigned) time(NULL)+1);
    bool should_swap_signs = rand() % 2;
    if (should_swap_signs) swap(sign1, sign2); // the contents of

    grid = Grid(size);
    // if (with_computer) {

    // }

    cout << "Player " << name1 << " has sign " << sign1 << ".\n"; 
    cout << "Player " << name2 << " has sign " << sign2 << ".\n"; 
    cout << endl;

    cout << "Player " << name1 << " begins.\n\n";
    cout << "  -  -  -  -  -  -  -  - \n\n";

    grid.display();

}

void Game::play() {

    char who_won = ' ';
    while (true) {
        who_won = turn(grid, name1, sign1);
        if (who_won != ' ') break;

        who_won = turn(grid, name2, sign2);
        if (who_won != ' ') break;
    }

    // F stands for Full
    if (who_won == 'F') {
        cout << "The game ended in a draw.\n";
        return;
    }

    string winner = (who_won == sign1) ? name1 : name2;
    cout << "Congratulations!\nPlayer " << winner << " won!";

    return;
}

// 'X' or 'O' if one of them won
// 'F' if the board is full with no wins -> draw
// ' ' game should continue  
char Game::turn(Grid &grid, const string name, const char sign) {
    char who_won = ' '; 
    Pos m;

    if (name == "Computer")
        m = computer_move(grid, sign);
    else
        m = player_move(grid, name, sign);
    
    grid.display();
    if (grid.check(m, sign)) {
        who_won = sign;
    }
    if (options(grid).empty()) {
        who_won = 'F';
    }

    return who_won;
}

Pos Game::computer_move(Grid &grid, const char sign) {
    auto move = find_best(grid, sign);
    grid.put(move, sign);
    cout << "Player Computer moves at:\n";
    cout << move.x << " " << move.y << "\n";
    return move;
}

Pos Game::player_move(Grid &grid, const string name, const char sign) {

    Pos p;
    cout << "Player " << name << " moves at:\n";
    cin >> p.x >> p.y;

    if (p.inrange(grid.getsize()) && (grid.at(p)==' ')) {
        grid.put(p, sign);
    }
    else {
        cout << "Invalid move. You lose your turn!\n";
    }

    return p;
}