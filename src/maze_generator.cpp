#include "maze_generator.hpp"
#include "types.hpp"
#include "utils.hpp"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <map>
#include <random>
#include <set>
#include <utility>
#include <vector>

struct dsu
{
    map<point, point> parent;
    map<point, int>   sz;

    void make_set(point p)
    {
        parent[p] = p;
        sz[p]     = 1;
    }

    point find_set(point p)
    {
        if (p == parent.at(p))
            return p;
        return parent[p] = find_set(parent.at(p));
    }

    void union_sets(point a, point b)
    {
        a = find_set(a);
        b = find_set(b);
        if (a != b)
        {
            if (sz[a] < sz[b])
                swap(a, b);
            parent[b] = a;
            sz[a] += sz[b];
        }
    }
    bool disjoint(vector<point> v1, vector<point> v2)
    {
        vector<point> temp(v1);
        temp.insert(temp.end(), v2.begin(), v2.end());

        for (int i = 0; i < (int)temp.size() - 1; ++i)
        {
            for (int j = i + 1; j < (int)temp.size(); ++j)
            {
                if (find_set(temp[i]) == find_set(temp[j]))
                    return false;
            }
        }
        return true;
    }
    void print_parents(maze &m)
    {
        for (int row = 0; row < m.rows; ++row)
        {
            for (int col = 0; col < m.cols; ++col)
            {
                cout << pp(find_set({row, col}));
            }
            cout << endl;
        }
    }
};

maze generate_maze(int rows, int cols, optional<unsigned> _seed)
{
    using edge = pair<point, point>;
    unsigned seed;
    if (_seed)
        seed = _seed.value();
    else
        seed = chrono::system_clock::now().time_since_epoch().count();

    maze                           m(rows, cols, WALL);
    vector<edge>                   edges;
    set<edge>                      visited;
    dsu                            d;
    function<bool(const point &p)> is_wall = [&m](point p) {
        return m.is_wall(p);
    };
    function<bool(const point &p)> is_empty = [&m](point p) {
        return m.is_empty(p);
    };
    function<bool(edge, edge)> cmp = [&m](edge e1, edge e2) {
        auto [x1, y1] = e1;
        auto [x2, y2] = e2;
        return (m.is_bound(x1) or m.is_bound(y1)) <
               (m.is_bound(x2) or m.is_bound(y2));
    };

    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < cols; ++col)
        {
            point p = make_pair(row, col);
            for (auto neighbor : m.neighbors(p, seed))
            {
                if (neighbor > p and not(m.is_bound(p) or m.is_bound(neighbor)))
                {
                    edges.push_back(make_pair(p, neighbor));
                }
            }
            d.make_set(p);
        }
    }

    shuffle(begin(edges), end(edges), default_random_engine(seed));

    // sort(edges.begin(), edges.end(), cmp);

    for (auto edge : edges)
    {
        if (visited.find(edge) != visited.end())
            continue;

        auto [p1, p2] = edge;
        visited.insert(edge);

        auto v1 = m.neighbors(p1, seed);
        v1.erase(remove(v1.begin(), v1.end(), p2), v1.end());
        v1 = filter(v1, is_empty);

        auto v2 = m.neighbors(p2, seed);
        v2.erase(remove(v2.begin(), v2.end(), p1), v2.end());
        v2 = filter(v2, is_empty);

        if (d.disjoint(v1, v2))
        {
            m.m[p1.first][p1.second] = EMPTY;
            m.m[p2.first][p2.second] = EMPTY;
            v1.push_back(p1);
            v2.push_back(p2);
            for (auto x : v1)
            {
                for (auto y : v2)
                {
                    d.union_sets(x, y);
                }
            }
        }
    }

    for (int col = 1; col < cols - 1; ++col)
    {
        if (m.m[1][col] == EMPTY)
        {
            m.m[0][col] = START;
            m.start     = make_pair(0, col);
            break;
        }
    }

    for (int col = cols - 2; col > 0; --col)
    {
        if (m.m[m.rows - 2][col] == EMPTY)
        {
            m.m[m.rows - 1][col] = EXIT;
            m.target             = make_pair(m.rows - 1, col);
            break;
        }
    }
    return m;
}
