#ifndef TYPES_HPP
#define TYPES_HPP

#include <string>
#include <utility>
#include <vector>
using namespace std;

enum cell_type
{
    WALL,
    EMPTY,
    START,
    EXIT,
    PATH_POINT
};
enum algorithm_type
{
    DEPTH_FIRST_SEARCH,
    BREADTH_FIRST_SEARCH,
    BEST_FIRST_SEARCH,
    A_STAR_SEARCH,
    HILL_CLIMBING
};

enum distance_type
{
    EUCLIDEAN,
    MANHATTAN
};

using maze_type = vector<vector<cell_type>>;
using point     = pair<int, int>;
using path      = vector<point>;

struct maze
{
    int       rows, cols;
    point     start;  // initial row and column
    point     target; // target row and column
    maze_type m;
    bool      is_wall(point p) const
    {
        auto [r, c] = p;
        return m[r][c] == WALL;
    }
    bool is_within_bounds(point p) const
    {
        auto [r, c] = p;
        return (0 <= r and r < rows and 0 <= cols and c < cols);
    }
    bool is_valid(point p) const
    {
        return is_within_bounds(p) and not is_wall(p);
    }
};

struct options
{
    algorithm_type algorithm;
    distance_type  distance_metric;
};

using algorithm = function<path(maze, options)>;

#endif
