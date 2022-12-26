#include <vector>
#include "utils.hpp"

std::vector<Pos> options(const Grid &grid);
int evaluate(int depth, Grid &grid, Pos p, char sign); 
Pos find_best(Grid &grid, char sign);