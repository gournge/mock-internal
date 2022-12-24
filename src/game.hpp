#include <string>
#include "utils.hpp"

using std::string;

class Game
{
    public:
        Game();
        void play();

    private: 
        int size;
        bool with_computer;
        bool computer_first;
        string name1, name2;
        char sign1 = 'O', sign2 = 'X';

        Grid grid;
    
        char turn(Grid &grid, const string name, const char sign);
        Pos player_move(Grid &grid, const string name, const char sign);
        Pos computer_move(Grid &grid, const char sign);

};