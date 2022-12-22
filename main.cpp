#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include "utils.hpp"
#include "computer.hpp"

using namespace std;

#define SAY(OUT) {cout << OUT << "\n";}
#define ASK(IN, OUT) {cout << OUT; cin >> IN; cout << "\n";}

void gather_data(int &size, bool &with_computer, string &name1, string &name2, char &sign1, char &sign2);
void player_move(Grid &grid, char &who_won, string name, char sign);
void computer_move(Grid &grid, char &who_won, char &sign);

int main() {

    // gather the data

    int size;
    bool with_computer;
    string name1, name2;
    char sign1 = 'O', sign2 = 'X';

    gather_data(size, with_computer, name1, name2, sign1, sign2);

    Grid grid(size);


    srand((unsigned) time(NULL));
    bool computer_first = rand() % 2;

    char who_won = ' ';
    do {

        if (with_computer) {

            if(computer_first) {
                computer_move(grid, who_won, sign1);
                if (options(grid).empty()) break;
                player_move(grid, who_won, name2, sign2);

            } else {
                player_move(grid, who_won, name2, sign2);
                if (options(grid).empty()) break;
                computer_move(grid, who_won, sign1);
            }

        } else {
            player_move(grid, who_won, name1, sign1);
            if (options(grid).empty()) break;
            player_move(grid, who_won, name2, sign2);
        }

    } while (who_won == ' ' and !options(grid).empty());

    if (who_won == ' ') {
        cout << "The game ended in a draw.";
        return 0;
    }

    auto winner = (who_won == 'X') ? name2 : name1;
    cout << "Congratulations!\nPlayer " << winner << " won!";

    return 0;
}

void gather_data(int &size, bool &with_computer, string &name1, string &name2, 
                                                   char &sign1,   char &sign2) {

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

    if (!with_computer) {
        // randomly changing the order of playing; always name1, name2
        srand((unsigned) time(NULL));
        bool should_swap = rand() % 2;
        if (should_swap) swap(name1, name2); // the contents of
    } else {
        srand((unsigned) time(NULL));
        bool should_swap = rand() % 2;
        if (should_swap) swap(sign1, sign2); // the contents of
    }

}

void computer_move(Grid &grid, char &who_won, char &sign) {
    auto move = find_best(grid, sign);
    grid.put(move, sign);
    who_won = grid.check(move, sign) ? sign : ' ';

    grid.display();
}

void player_move(Grid &grid, char &who_won, string name, char sign) {

    Pos p;
    cout << "Player " << name << " moves at:\n";
    cin >> p.x >> p.y;

    if (p.inrange(grid.size) && (grid.at(p)==' ')) {
        grid.put(p, sign);
        if (grid.check(p, sign)) who_won = sign;
    }
    else {
        cout << "Invalid move. You lose your turn!\n";
    }

    who_won = grid.check(p, sign) ? sign : ' ';

    grid.display();
}