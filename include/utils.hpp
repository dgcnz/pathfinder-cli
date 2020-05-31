#ifndef UTILS_HPP
#define UTILS_HPP

#include "types.hpp"
#include "utils.hpp"
#include <string>

char cell_type_to_char(cell_type cell);

cell_type char_to_cell_type(char c);

maze read_maze(string filename);

void print_maze(maze m);

#endif
