#include "types.hpp"
#include "utils.hpp"

#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

path best_first_search(maze m, opt_payload o)
{
    point target = m.target;

    map<point, point> came_from;
    map<point, bool>  visited;

    auto dist         = o.dist;
    auto h            = [dist, target](point p) { return dist(p, target); };
    auto f            = [h](point p) { return h(p); };
    auto increasing_f = [f](point p1, point p2) -> bool {
        return f(p1) < f(p2);
    };
    multiset<point, decltype(increasing_f)> frontier(increasing_f);

    frontier.insert(m.start);

    while (not frontier.empty())
    {
        point current    = *frontier.begin();
        visited[current] = true;

        if (current == target)
            return reconstruct_path(came_from, current);

        frontier.erase(frontier.begin());

        for (auto q : neighbors(current, m))
        {
            if (m.is_wall(q))
                continue;
            if (visited.find(q) == visited.end()) // not visited
            {
                came_from[q] = current;
                frontier.insert(q);
            }
        }
    }
    cout << "NO PATH WAS FOUND" << endl;
    return {}; // No path was found
}
