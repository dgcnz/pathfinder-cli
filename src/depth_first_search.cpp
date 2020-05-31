#include "depth_first_search.hpp"
#include "types.hpp"
#include "utils.hpp"

#include <utility>
#include <vector>

using vvb = vector<vector<bool>>;

vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

vector<point> get_next_points(point p, maze &m)
{
    vector<point> ans;
    for (auto [dr, dc] : directions)
    {
        point q = make_pair(p.first + dr, p.second + dc);
        if (m.is_valid(q))
            ans.push_back(q);
    }
    return ans;
}

bool dfs_util(point p, maze &m, vvb &vis, path &ans)
{
    if (vis[p.first][p.second])
        return false;

    ans.push_back(p);
    if (p == m.target)
        return true;

    vis[p.first][p.second] = true;

    for (point q : get_next_points(p, m))
        if (dfs_util(q, m, vis, ans))
            return true;

    ans.pop_back();
    return false;
}
path depth_first_search(maze m, options o)
{
    (void)(o); // unused parameter trick
    path p;
    vvb  vis(m.rows, vector(m.cols, false)); // be careful with huge maze sizes!

    dfs_util(m.start, m, vis, p);

    return p;
}
