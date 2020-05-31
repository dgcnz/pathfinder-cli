#ifndef TYPES_HPP
#define TYPES_HPP

#include <vector>
using namespace std;

enum cell_type
{
    WALL,
    EMPTY,
    START,
    EXIT
};

using maze_type = vector<vector<cell_type>>;

struct maze
{
    int       rows, cols;
    maze_type m;
};

#endif
