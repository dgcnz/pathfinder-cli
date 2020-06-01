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

path reconstruct_path(map<point, point> came_from, point current)
{
    path ans;
    ans.push_back(current);

    while (came_from.find(current) != came_from.end())
    {
        current = came_from[current];
        ans.push_back(current);
    }

    reverse(ans.begin(), ans.end());
    return ans;
}

string ppoint(point p)
{
    string ans;
    ans += "(";
    ans += to_string(p.first);
    ans += ", ";
    ans += to_string(p.second);
    ans += ")";
    return ans;
}

path a_star_search(maze m, options o)
{
    const int INF = INT_MAX;
    // defaults to euclidean
    point target = m.target;

    map<point, int>   _g;
    map<point, point> came_from;
    auto dist = (o.distance_metric == MANHATTAN ? manhattan : euclidean);
    auto g    = [&_g](point p) -> int {
        if (_g.find(p) == _g.end())
            return INF;
        else
            return _g.at(p);
    };
    auto h = [dist, target](point p) -> int { return dist(p, target); };
    auto f = [g, h](point p) -> int {
        if (g(p) == INF)
            return INF;
        else
            return h(p) + g(p);
    };
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
            int tentative_g =
                (g(current) == INF ? INF : g(current) + dist(current, q));

            if (g(q) == INF or tentative_g < g(q))
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
