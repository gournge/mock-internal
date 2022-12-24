#include <iostream>
#include "computer.hpp"
#include "utils.hpp"

int main()
{

    int size = 5;
    Grid grid(size);

    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            grid.put({x, y}, '0' + y*size + x);
        }
    }

    grid.display();

    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            grid.put({x, y}, ' ');
        }
    }


    grid.put({4, 1}, 'X');
    grid.put({3, 2}, 'X');
    grid.put({2, 3}, 'X');
    grid.put({1, 4}, 'X');

    // // grid.put({0, 0}, 'X');
    // grid.put({1, 1}, 'X');
    // grid.put({2, 2}, 'X');

    // grid.put({2, 1}, 'X');

    Pos p = {1, 4};

    grid.put(p, '0');
    grid.display();
    grid.put(p, 'X');


    cout << grid.check({2, 2}, 'X');


    return 0;
}

