#ifndef TYPES_HPP
#define TYPES_HPP

#include <limits>
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

struct maze
{
    using point = pair<int, int>;
    int                       rows, cols;
    point                     start;  // initial row and column
    point                     target; // target row and column
    vector<vector<cell_type>> m;
    maze() {}
    maze(int rows, int cols, cell_type ct = EMPTY) : rows(rows), cols(cols)
    {
        m = vector(rows, vector(cols, ct));
    }
    bool is_wall(point p) const
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

struct opt_payload
{
    using point           = pair<int, int>;
    using distance_metric = function<double(point, point)>;
    distance_metric dist;
};

using point           = pair<int, int>;
using path            = vector<point>;
using distance_metric = function<double(point, point)>;
using algorithm       = function<path(maze, opt_payload)>;
const double _INF     = std::numeric_limits<double>::infinity();

#endif
