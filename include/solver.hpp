#ifndef SOLVER_HPP
#define SOLVER_HPP
#include "a_star_search.hpp"
#include "best_first_search.hpp"
#include "breadth_first_search.hpp"
#include "depth_first_search.hpp"
#include "hill_climbing.hpp"
#include "types.hpp"
#include <map>

map<algorithm_type, algorithm> get_function = {
    {DEPTH_FIRST_SEARCH, depth_first_search},
    {BREADTH_FIRST_SEARCH, breadth_first_search},
    {BEST_FIRST_SEARCH, best_first_search},
    {A_STAR_SEARCH, a_star_search},
    {HILL_CLIMBING, hill_climbing}};

path solve(maze m, options o) { return (get_function[o.algorithm])(m, o); }

#endif
