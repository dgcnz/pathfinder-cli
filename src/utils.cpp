#include "utils.hpp"
#include "types.hpp"
#include <cmath>
#include <exception>
#include <fstream>
#include <iostream>
#include <map>

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

    imaze.rows = rows;
    imaze.cols = cols;
    imaze.m    = vector(rows, vector<cell_type>(cols, EMPTY));

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
    string highlightc = "\033[0;#32m";
    string defaultc   = "\033[0m";

    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < cols; ++col)
        {
            try
            {
                if (m.m[row][col] == PATH_POINT)
                    cout << "\033[1;31m" << cell_type_to_char(m.m[row][col])
                         << "\033[0m";
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

map<string, algorithm_type> get_algo = {
    {"DEPTH_FIRST_SEARCH", DEPTH_FIRST_SEARCH},
    {"BREADTH_FIRST_SEARCH", BREADTH_FIRST_SEARCH},
    {"BEST_FIRST_SEARCH", BEST_FIRST_SEARCH},
    {"A_STAR_SEARCH", A_STAR_SEARCH},
    {"HILL_CLIMBING", HILL_CLIMBING}};

map<string, distance_type> get_distance_metric = {{"EUCLIDEAN", EUCLIDEAN},
                                                  {"MANHATTAN", MANHATTAN}};

options read_options(vector<string> argv)
{
    // TODO: It's too ad-hoc
    if (get_algo.find(argv[0]) != get_algo.end())
    {
        if (argv.size() >= 2)
            return {get_algo[argv[0]], get_distance_metric[argv[1]]};
        else
            return {get_algo[argv[0]], EUCLIDEAN};
    }
    else
    {
        string s;
        for (auto const &[k, v] : get_algo)
            s += k + '\n';

        throw invalid_argument("Invalid algorithm. Options are:\n" + s);
    }
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

int euclidean(point p1, point p2)
{
    return (int)sqrt((int)pow(p1.first - p2.first, 2) +
                     (int)pow(p1.second - p2.second, 2));
}

int manhattan(point p1, point p2)
{
    return (int)abs(p1.first - p2.first) + abs(p1.second - p2.second);
}

vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

vector<point> neighbors(point p, maze &m)
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
