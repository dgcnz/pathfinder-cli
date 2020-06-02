#include "hill_climbing.hpp"
#include "types.hpp"
#include "utils.hpp"
#include <climits>
#include <iostream>
#include <map>

// algorithm Discrete Space Hill Climbing is
//     currentNode := startNode
//     loop do
//         L := NEIGHBORS(currentNode)
//         nextEval := −INF
//         nextNode := NULL
//         for all x in L do
//             if EVAL(x) > nextEval then
//                 nextNode := x
//                 nextEval := EVAL(x)
//         if nextEval ≤ EVAL(currentNode) then
//             // Return current node since no better neighbors exist
//             return currentNode
//         currentNode := nextNode
//

string pp(point p)
{
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

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
            cout << "TESTING" << pp(x) << ": " << h(x) << " < " << next_eval
                 << "? " << (h(x) < next_eval) << endl;
            if (h(x) < next_eval)
            {
                next_node = x;
                next_eval = h(x);
            }
        }

        cout << "PROGRESS" << pp(next_node) << ": " << h(next_node)
             << " >= " << pp(cur_node) << ": " << h(cur_node) << "? "
             << (h(next_node) >= h(cur_node)) << endl;
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
