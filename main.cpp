#include <iostream>
#include "game.hpp"

int main() {

    std::string again;
    do {
        Game game;
        game.play();
        
        do {
        std::cout << "Do you want to play again? (0/1) ";
        std::cin >> again;
        } while ((again != "0") && (again != "1"));

    } while(again == "1");

    return 0;
}

