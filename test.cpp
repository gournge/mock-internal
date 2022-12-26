#include <iostream>
#include <chrono>
#include "computer.hpp"
#include "utils.hpp"

using std::cout;

void test1();
void test1andhalf();
void test2();
void test3();
void test4();
void test5();


int main()
{

    // test1();

    test1andhalf();

    // test2();

    // test3();

    // test4();

    // test5();


    return 0;
}

void test1() {

    // X's turn
    //  | | | |X
    // ---------
    //  | | |X| 
    // ---------
    //  | |X| | 
    // ---------
    //  |X| | | 
    // ---------
    //  | | | | 

    Grid grid(5);

    grid.put({4, 0}, 'X');
    grid.put({3, 1}, 'X');
    grid.put({2, 2}, 'X');
    grid.put({1, 3}, 'X');

    Pos p = {0, 4};

    grid.put(p, '0');
    grid.display();
    grid.put(p, ' ');

    cout << evaluate(5, grid, p, 'X');

    auto b = find_best(grid, 'X');
    std::cout << b.x << " " << b.y << "\n";

    // cout << grid.check(p, 'X');
}

void test1andhalf() {

    Grid grid(3);

    grid.put({0, 0}, 'X');
    grid.put({2, 2}, 'O');
    grid.put({0, 2}, 'X');
    grid.put({0, 1}, 'O');

    grid.put({1, 0}, 'O');
    grid.put({1, 1}, 'O');
    grid.put({1, 2}, 'X');

    // grid.display();

    auto b = find_best(grid, 'X');
    std::cout << b.x << " " << b.y << "\n";

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

    // cout << evaluate(9, grid, {0, 1}, 'X') << "\n";

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

    const int max_depth = 10;

    cout << evaluate(max_depth, grid, {0, 0}, 'O') << "\n";

    cout << evaluate(max_depth, grid, {2, 3}, 'O') << "\n";

    cout << evaluate(max_depth, grid, {1, 1}, 'O') << "\n";

    // auto b = find_best(grid, 'O');
    // std::cout << b.x << " " << b.y << "\n";

}

void test5() {

    //  | | | | | | | | | 
    // -------------------
    //  | | | | | | | | |
    // -------------------
    //  | | | | | |X| | |
    // -------------------
    //  | | | | |X| | | |
    // -------------------
    //  | | | | | | | | |
    // -------------------
    //  | | |X| | | | | |
    // -------------------
    //  | |X| | | | | | |
    // -------------------
    //  | | | | | | | | | 
    // -------------------
    //  | | | | | | | | |
    // -------------------
    //  | | | | | | | | |

    Grid grid(10);

    grid.put({6, 2}, 'X');
    grid.put({5, 3}, 'X');

    grid.put({3, 5}, 'X');
    grid.put({2, 6}, 'X');

    grid.display();    

    Pos p{4, 4};

    auto start = std::chrono::high_resolution_clock::now();

    // cout << evaluate(10, grid, p, 'X') << "\n";

    auto b = find_best(grid, 'X');
    cout << b.x << " " << b.y << "\n";

    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start);

    cout << "Time taken: " << duration.count() << " microseconds.\n";

}