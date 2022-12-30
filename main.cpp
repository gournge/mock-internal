#include <iostream>
#include "game.hpp"

int main() {

    bool again;
    do {
        Game game;
        game.play();
        
        std::cout << "Do you want to play again? (0/1) ";
        std::cin >> again;
    } while(again);

    return 0;
}