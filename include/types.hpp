#ifndef TYPES_HPP
#define TYPES_HPP

#include <limits>
#include <optional>
#include <random>
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

    vector<pair<int, int>> directions = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    maze() {}
    maze(int rows, int cols, cell_type ct = EMPTY) : rows(rows), cols(cols)
    {
        m = vector(rows, vector(cols, ct));
    }
    bool is_empty(point p) const
    {
        auto [r, c] = p;
        return m[r][c] == EMPTY;
    }
    bool is_wall(point p) const
    {
        auto [r, c] = p;
        return m[r][c] == WALL;
    }
    bool is_bound(point p) const
    {
        auto [r, c] = p;
        return (r == 0 or r == rows - 1) or (c == 0 or c == cols - 1);
    }
    bool is_within_bounds(point p) const
    {
        auto [r, c] = p;
        return (0 <= r and r < rows and 0 <= c and c < cols);
    }
    bool is_valid(point p) const
    {
        return is_within_bounds(p) and not is_wall(p);
    }

    vector<point> neighbors(point p, optional<unsigned> seed = nullopt)
    {
        vector<point> ans;
        for (auto [dr, dc] : directions)
        {
            point q = make_pair(p.first + dr, p.second + dc);
            if (this->is_within_bounds(q))
                ans.push_back(q);
        }

        unsigned _seed;
        if (seed)
            _seed = seed.value();
        else
            _seed = chrono::system_clock::now().time_since_epoch().count();

        shuffle(begin(ans), end(ans), default_random_engine(_seed));
        return ans;
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
