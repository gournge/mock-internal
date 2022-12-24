#include <iostream>
#include "computer.hpp"
#include "utils.hpp"

void test1();
void test2();
void test3();
void test4();


int main()
{

    // test1();

    // test2();

    test3();

    // test4();

    return 0;
}

void test1() {

    Grid grid(5);

    grid.put({4, 1}, 'X');
    grid.put({3, 2}, 'X');
    grid.put({2, 3}, 'X');
    grid.put({1, 4}, 'X');

    grid.put({0, 1}, 'X');
    grid.put({0, 2}, 'X');

    Pos p = {0, 0};

    grid.put(p, '0');
    grid.display();
    grid.put(p, 'X');

    cout << evaluate(grid, p, 'X');

    // cout << grid.check(p, 'X');
}

void test2() {

    // X's turn: 
    // 
    // X| |
    // -----
    // O| |
    // -----
    // X| |O
    // 

    Grid grid(3);

    grid.put({0, 0}, 'X');
    grid.put({2, 2}, 'O');
    grid.put({0, 2}, 'X');
    grid.put({0, 1}, 'O');

    grid.display();

    // grid.put({2, 0}, 'X');

    // cout << evaluate(grid, {1, 0}, 'X');

    auto b = find_best(grid, 'X');
    std::cout << b.x << " " << b.y << "\n";

}

void test3() {

    // O's turn: 
    // 
    //  | |X
    // -----
    //  | |
    // -----
    // X| |O
    //

    Grid grid(3);

    grid.put({2, 0}, 'X');
    grid.put({2, 2}, 'O');
    grid.put({0, 2}, 'X');

    grid.display();

    auto b = find_best(grid, 'O');
    std::cout << b.x << " " << b.y << "\n";

}

void test4() {

    // O's turn: 
    // 
    //  | |X| 
    // -------
    //  | | |
    // -------
    // X| |O|
    // -------
    //  | | |
    //
    // ans: 1 1

    Grid grid(4);

    grid.put({2, 0}, 'X');
    grid.put({2, 2}, 'O');
    grid.put({0, 2}, 'X');

    grid.display();

    cout << evaluate(grid, {0, 0}, 'O') << "\n";

    cout << evaluate(grid, {2, 3}, 'O') << "\n";

    cout << evaluate(grid, {1, 1}, 'O') << "\n";

    // auto b = find_best(grid, 'O');
    // std::cout << b.x << " " << b.y << "\n";

}