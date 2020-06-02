#include "a_star_search.hpp"
#include "types.hpp"
#include "utils.hpp"

#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

path a_star_search(maze m, opt_payload o)
{
    point target = m.target;

    map<point, double> _g;
    map<point, point>  came_from;

    auto dist = o.dist;
    auto h    = [dist, target](point p) { return dist(p, target); };
    auto g    = [&_g](point p) {
        if (_g.find(p) == _g.end())
            return _INF;
        else
            return _g.at(p);
    };
    auto f            = [g, h](point p) { return h(p) + g(p); };
    auto increasing_f = [f](point p1, point p2) -> bool {
        return f(p1) < f(p2);
    };
    multiset<point, decltype(increasing_f)> frontier(increasing_f);

    _g[m.start] = 0;
    frontier.insert(m.start);

    while (not frontier.empty())
    {
        point current = *frontier.begin();
        if (current == target)
            return reconstruct_path(came_from, current);

        frontier.erase(frontier.begin());

        for (auto q : neighbors(current, m))
        {
            auto tentative_g = g(current) + dist(current, q);

            if (g(q) == _INF or tentative_g < g(q))
            {
                came_from[q] = current;
                _g[q]        = tentative_g;

                frontier.insert(q);
            }
        }
    }
    cout << "NO PATH WAS FOUND" << endl;
    return {}; // No path was found
}
