#ifndef TYPES_HPP
#define TYPES_HPP

#include <string>
#include <vector>
using namespace std;

enum cell_type
{
    WALL,
    EMPTY,
    START,
    EXIT
};
enum algorithm_type
{
    DEPTH_FIRST_SEARCH,
    BREADTH_FIRST_SEARCH,
    BEST_FIRST_SEARCH,
    A_STAR_SEARCH,
    HILL_CLIMBING
};

using maze_type = vector<vector<cell_type>>;
using path      = vector<pair<int, int>>;

struct maze
{
    int       rows, cols;
    maze_type m;
};

struct options
{
    algorithm_type algorithm;
};

using algorithm = function<path(maze, options)>;

#endif
