#include <vector>
#include "utils.hpp"

using std::vector;

vector<Pos> options(const Grid &grid);
int evaluate(const Grid &grid, Pos p); 
Pos find_best(Grid &grid, char sign);