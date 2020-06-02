#include "utils.hpp"
#include "a_star_search.hpp"
#include "best_first_search.hpp"
#include "breadth_first_search.hpp"
#include "depth_first_search.hpp"
#include "hill_climbing.hpp"
#include "types.hpp"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <exception>
#include <fstream>
#include <iostream>
#include <map>
#include <random>

char cell_type_to_char(cell_type cell)
{
    char c;
    switch (cell)
    {
    case EMPTY:
        c = '*';
        break;
    case WALL:
        c = '-';
        break;
    case START:
        c = '#';
        break;
    case EXIT:
        c = '$';
        break;
    case PATH_POINT:
        c = 'o';
        break;
    default:
        throw invalid_argument("Unrecognized cell type.");
    }
    return c;
}

cell_type char_to_cell_type(char c)
{
    cell_type cell;
    switch (c)
    {
    case '*':
        cell = EMPTY;
        break;
    case '-':
        cell = WALL;
        break;
    case '#':
        cell = START;
        break;
    case '$':
        cell = EXIT;
        break;
    case 'o':
        cell = PATH_POINT;
        break;
    default:
        throw invalid_argument("Unrecognized character.");
    }
    return cell;
}

maze read_maze(string filename)
{
    int      rows, cols;
    char     c;
    ifstream maze_file;
    maze     imaze;

    maze_file.open(filename);
    maze_file >> rows >> cols;

    imaze = maze(rows, cols, EMPTY);

    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < cols; ++col)
        {
            maze_file >> c;
            try
            {
                imaze.m[row][col] = char_to_cell_type(c);
                if (imaze.m[row][col] == START)
                    imaze.start = make_pair(row, col);
                else if (imaze.m[row][col] == EXIT)
                    imaze.target = make_pair(row, col);
            }
            catch (const invalid_argument &e)
            {
                cout << "Invalid character on input maze file." << endl;
            }
        }
    }

    maze_file.close();
    return imaze;
}

void print_maze(maze m)
{
    int rows, cols;
    rows = m.rows, cols = m.cols;
    string highlightc = "\033[1;31m";
    string defaultc   = "\033[0m";

    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < cols; ++col)
        {
            try
            {
                if (m.m[row][col] == PATH_POINT)
                    cout << highlightc << cell_type_to_char(m.m[row][col])
                         << defaultc;
                else
                    cout << cell_type_to_char(m.m[row][col]);
            }
            catch (const invalid_argument &e)
            {
                cout << "Invalid cell_type on output maze." << endl;
            }
        }
        cout << endl;
    }
    cout << endl;
}

double euclidean(point p1, point p2)
{
    return sqrt(pow(p1.first - p2.first, 2) + pow(p1.second - p2.second, 2));
}

double manhattan(point p1, point p2)
{
    return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}
map<string, algorithm> get_algorithm = {
    {"depth_first_search", depth_first_search},
    {"breadth_first_search", breadth_first_search},
    {"best_first_search", best_first_search},
    {"a_star_search", a_star_search},
    {"hill_climbing", hill_climbing}};

map<string, distance_metric> get_distance_metric = {{"euclidean", euclidean},
                                                    {"manhattan", manhattan}};

pair<algorithm, opt_payload> parse_options(string r_algorithm, string r_dist)
{
    algorithm   fx   = get_algorithm[r_algorithm];
    opt_payload opts = {get_distance_metric[r_dist]};
    return {fx, opts};
}

void print_path(path p)
{
    for (auto [r, c] : p)
        cout << "(" << r << ", " << c << ") ";
    cout << endl;
}

maze paint_maze(const maze &m, path p)
{
    maze ans = m;
    for (auto [r, c] : p)
        ans.m[r][c] = PATH_POINT;

    return ans;
}

void save_maze(const maze &m, string filename)
{
    int      rows, cols;
    ofstream maze_file;

    maze_file.open(filename);
    rows = m.rows;
    cols = m.cols;

    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < cols; ++col)
        {
            try
            {
                maze_file << cell_type_to_char(m.m[row][col]);
            }
            catch (const invalid_argument &e)
            {
                cout << "Invalid cell_type on maze." << endl;
            }
        }
        maze_file << endl;
    }

    maze_file << endl;

    maze_file.close();
}

vector<pair<int, int>> directions = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

vector<point> neighbors(point p, maze &m)
{
    vector<point> ans;
    for (auto [dr, dc] : directions)
    {
        point q = make_pair(p.first + dr, p.second + dc);
        if (m.is_valid(q))
            ans.push_back(q);
    }

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(begin(ans), end(ans), default_random_engine(seed));
    return ans;
}

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
