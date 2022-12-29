#include <vector>
#include "utils.hpp"

int evaluate(int depth, Grid &grid, const int p, const char sign);
Pos find_best(Grid &grid, char sign, int depth = -1);