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
void test6();
void test7();


int main()
{

    Grid grid(5);
    grid.put({2, 2}, 'X');
    grid.display();
    grid.put({2, 2}, ' ');
    grid.display();

    // cout << grid.convert();

    // test7();

    // test1();

    // test1andhalf();

    // test2();

    // test3();

    // test4();

    // test5();

    // test6();

    return 0;
}

void test7() {
    Grid grid(5); 

    grid.put({2, 2}, 'X');
    // grid.put({2, 3}, 'O');
    // grid.put({6, 4}, 'X');

    grid.display();

    // auto check_order = grid.get_cell_check_order();
    // for (int y = 0; y<grid.get_size(); y++) {
    //     for (int x = 0; x<grid.get_size(); x++) {
    //         cout << check_order[grid.convert({x, y})] << ' ';
    //     }
    //     cout << "\n";
    // }

    // auto spiral = spiral_from_middle_decreasing(grid.get_size());
    // for (auto el : spiral)
    //     cout << el << " ";
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

    // cout << evaluate(5, grid, p, 'X');

    auto b = find_best(grid, 'X');
    std::cout << b.x << " " << b.y << "\n";

    // cout << grid.check(p, 'X');
}

void test1andhalf() {

    // X|O|   
    // -----  
    // O|O|   
    // -----  
    // X|X|O  

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

    // cout << evaluate(9, grid, {1, 1}, 'O') << "\n";
    // cout << evaluate(9, grid, {2, 0}, 'X') << "\n";

    // cout << evaluate(9, grid, {1, 0}, 'X') << "\n";

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
    // ans: random 

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

    // const int max_depth = 10;

    // cout << evaluate(max_depth, grid, {0, 0}, 'O') << "\n";

    // cout << evaluate(max_depth, grid, {2, 3}, 'O') << "\n";

    // cout << evaluate(max_depth, grid, {1, 1}, 'O') << "\n";

    auto b = find_best(grid, 'O');
    std::cout << b.x << " " << b.y << "\n";

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

void test6() {

    // O's turn 
    // O| | |
    // -------
    // O| | |
    // -------
    // X|O|X|
    // -------
    //  | | |

    Grid grid(4);

    grid.put({0, 0}, 'O');
    grid.put({0, 1}, 'O');
    grid.put({0, 2}, 'X');
    grid.put({1, 2}, 'O');
    grid.put({2, 2}, 'X');

    grid.display();

    cout << evaluate(5, grid, grid.convert({2, 3}), 'O') << "\n";

    auto b = find_best(grid, 'O');
    cout << b.x << " " << b.y << "\n";

}
