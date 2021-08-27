#include "depth_first_search.hpp"
#include "types.hpp"
#include "utils.hpp"

#include <utility>
#include <vector>

using namespace std;
using vvb = vector<vector<bool>>;

bool dfs_util(point p, maze &m, vvb &vis, path &ans)
{
    if (vis[p.first][p.second])
        return false;

    ans.push_back(p);
    if (p == m.target)
        return true;

    vis[p.first][p.second] = true;

    for (point q : m.neighbors(p))
    {
        if (m.is_wall(q))
            continue;
        if (dfs_util(q, m, vis, ans))
            return true;
    }

    ans.pop_back();
    return false;
}
path depth_first_search(maze m, opt_payload o)
{
    (void)(o); // unused parameter trick
    path p;
    vvb  vis(m.rows, vector(m.cols, false)); // be careful with huge maze sizes!

    dfs_util(m.start, m, vis, p);

    return p;
}
