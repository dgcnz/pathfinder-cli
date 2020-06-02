#include "breadth_first_search.hpp"
#include "types.hpp"
#include "utils.hpp"
#include <map>
#include <queue>

path breadth_first_search(maze m, opt_payload o)
{
    // TODO
    (void)(o); // remove if variable is used

    queue<point>      frontier;
    map<point, point> came_from;
    map<point, bool>  visited;

    point target = m.target;
    frontier.push(m.start);

    while (not frontier.empty())
    {
        point current = frontier.front();
        frontier.pop();
        visited[current] = true;

        if (current == target)
            return reconstruct_path(came_from, current);

        for (auto neighbor : neighbors(current, m))
        {
            if (visited.find(neighbor) == visited.end()) // not visited
            {
                came_from[neighbor] = current;
                frontier.push(neighbor);
            }
        }
    }

    return {};
}
