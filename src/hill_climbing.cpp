#include "hill_climbing.hpp"
#include "types.hpp"
#include "utils.hpp"
#include <climits>
#include <iostream>
#include <map>

path hill_climbing(maze m, opt_payload o)
{
    point             cur_node = m.start;
    point             target   = m.target;
    auto              dist     = o.dist;
    auto              h = [dist, target](point p) { return dist(p, target); };
    map<point, point> came_from;

    while (true)
    {
        auto  next_eval = _INF;
        point next_node = {};

        if (cur_node == target)
            return reconstruct_path(came_from, cur_node);

        for (point x : neighbors(cur_node, m))
        {
            if (h(x) < next_eval)
            {
                next_node = x;
                next_eval = h(x);
            }
        }

        if (next_eval >= h(cur_node))
        {
            cout << "STUCK ON LOCAL MAXIMA" << endl;
            return reconstruct_path(came_from, cur_node);
        }
        came_from[next_node] = cur_node;
        cur_node             = next_node;
    }

    return path();
}
