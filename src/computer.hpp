#include <vector>
#include "utils.hpp"

int evaluate(int depth, Grid &grid, const int p, const char sign, int& count);
Pos find_best(Grid &grid, char sign, int depth = -1);

std::vector<Pos> find_promising(Grid &grid, char sign);
std::vector<Pos> find_neighbors(Grid &grid, char sign, Pos cell);
