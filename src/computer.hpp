#include <vector>
#include "utils.hpp"

std::vector<Pos> options(const Grid &grid);
int evaluate(Grid &grid, Pos p, char sign); 
Pos find_best(Grid &grid, char sign);