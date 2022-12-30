#include <iostream>
#include <chrono>
#include "computer.hpp"

int main() {
    for (int size = 4; size<=10; size++) {
        Grid grid(size);
        char sign = 'X';

        std::cout << "At size: " << size << " optimal depths are: ";

        for (int move = 0; move<10; move++) {
            int depth = 0; Pos m{1, 2};
            std::chrono::microseconds duration;
            std::chrono::microseconds max_time(1'000'000);
            do {
                depth++;

                auto start = std::chrono::high_resolution_clock::now();

                // m = find_best(grid, sign, depth);
                std::cout << "hello\n";

                auto stop = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start); 
                
                // std::cout << m.x << " " << m.y << "\n";

                std::cout << duration.count() << " ";
            } while (duration.count() < max_time.count());
            std::cout << depth-1 << " ";

            grid.put(m, sign);
            sign = (sign == 'X') ? 'O' : 'X';
            // std::cout << " (" << grid.get_empty() << ") "; 
        }
        std::cout << "\n";
    }
}


