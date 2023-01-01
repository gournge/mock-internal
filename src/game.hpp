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
        bool show_time;
        string name1, name2;
        char sign1 = 'O', sign2 = 'X';

        Grid grid;
    
        char turn(const string name, const char sign);
        Pos player_move(const string name, const char sign);
        Pos computer_move(const char sign);

};

