#include <iostream>
#include <cstdlib>
#include <time.h>
#include <chrono>
#include "game.hpp"
#include "utils.hpp"
#include "computer.hpp"

// using namespace std;

using std::cout;
using std::cin;
using std::string;

#define ASK(IN, OUT) {cout << OUT; cin >> IN; cout << "\n";}

Game::Game() {

    // game size
    string str_size;
    bool valid;
    do {

        ASK(str_size, "Enter the size of the TicTacToe grid: (between 3 and 10) ");
        
        valid = (str_size == "3") || (str_size == "4") || 
                (str_size == "5") || (str_size == "6") || 
                (str_size == "7") || (str_size == "8") ||
                (str_size == "9") || (str_size == "10");

    } while (!valid);
    size = std::stoi(str_size);

    // whether to play with a computer
    string str_with_computer;
    do {
        ASK(str_with_computer, "Do you want to play with a computer? (0/1) ");
    } while ((str_with_computer != "0") && (str_with_computer != "1"));

    with_computer = (str_with_computer == "0") ? false : true;

    // whether to time the computer
    if (with_computer) {
        string str_show_time;
        do {
            ASK(str_show_time, "Do you want to show how long does the computer move? (0/1) ");
        } while ((str_show_time != "0") && (str_show_time != "1"));

        show_time = (str_show_time == "0") ? false : true;
    }

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

    srand((unsigned) time(NULL)+379);
    bool should_swap_signs = rand() % 2;
    if (should_swap_signs) std::swap(sign1, sign2); // the contents of

    grid = Grid(size);

    cout << "To enter coordinates of your move, first type in the column and then the row number.\n\n";

    cout << "Player " << name1 << " has sign " << sign1 << ".\n"; 
    cout << "Player " << name2 << " has sign " << sign2 << ".\n"; 
    cout << "\n";

    cout << "Player " << name1 << " begins.\n\n";
    cout << "  -  -  -  -  -  -  -  - \n\n";

}

void Game::play() {

    char who_won = ' ';
    while (true) {
        who_won = turn(name1, sign1);
        if (who_won != ' ') break;

        who_won = turn(name2, sign2);
        if (who_won != ' ') break;
    }

    // F stands for Full
    if (who_won == 'F') {
        cout << "The game ended in a draw.\n";
        return;
    }

    string winner = (who_won == sign1) ? name1 : name2;
    cout << "Congratulations!\nPlayer " << winner << " won!\n";

    return;
}

// 'X' or 'O' if one of them won
// 'F' if the board is full with no wins -> draw
// ' ' game should continue  
char Game::turn(const string name, const char sign) {
    char who_won = ' '; 
    Pos m;

    grid.display();

    if (name == "Computer")
        m = computer_move(sign);
    else
        m = player_move(name, sign);
    
    // if it is valid
    if (!(m == Pos{-1, -1})) {

    if (grid.check(m, sign)) {
        who_won = sign;
    }
    if (grid.get_empty() == 0) {
        who_won = 'F';
    }

    }

    return who_won;
}

Pos Game::computer_move(const char sign) {

    auto start = std::chrono::high_resolution_clock::now();

    Pos move = find_best(grid, sign);

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop-start);

    if (show_time) cout << "Time taken: " << duration.count() << " milliseconds.\n";

    grid.put(move, sign);
    cout << "Player Computer moves at:\n";
    cout << move.x << " " << move.y << "\n";
    return move;
}

// returns Pos{-1, -1} when it is invalid
Pos Game::player_move(const string name, const char sign) {

    bool x_valid, y_valid;
    string x, y;
    cout << "Player " << name << " moves at:\n";
    cin >> x >> y;

    x_valid = (x == "1") || (x == "2") ||
              (x == "3") || (x == "4") || 
              (x == "5") || (x == "6") || 
              (x == "7") || (x == "8") ||
              (x == "9") || (x == "0");

    y_valid = (y == "1") || (y == "2") ||
              (y == "3") || (y == "4") || 
              (y == "5") || (y == "6") || 
              (y == "7") || (y == "8") ||
              (y == "9") || (y == "0");

    bool input_valid = x_valid && y_valid;

    if (!input_valid) { 
        cout << "Invalid move. You lose your turn!\n";
        return {-1, -1};
    }
    Pos p{std::stoi(x), std::stoi(y)};

    if (p.inrange(grid.get_size()) && (grid.at(p)==' ')) {
        grid.put(p, sign);
    }
    else {
        cout << "Invalid move. You lose your turn!\n";
    }

    return p;
}



