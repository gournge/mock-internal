#include <iostream>
#include "computer.hpp"
#include "utils.hpp"

int main()
{
    Grid grid(3);

    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            grid.put({x, y}, '0' + y*3 + x);
        }
    }

    grid.display();

    grid.put({2, 0}, 'X');
    grid.put({1, 1}, 'X');
    grid.put({0, 2}, 'X');

    cout << grid.check({1, 1}, 'X');

    return 0;
}

