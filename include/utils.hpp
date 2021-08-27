#ifndef UTILS_HPP
#define UTILS_HPP

#include "types.hpp"
#include <functional>
#include <map>
#include <string>

/*! \fn char cell_type_to_char(cell_type cell)
    \brief Returns the corresponding character out of a cell_type.
    \param cell cell_type to be transformed to char
*/
char cell_type_to_char(cell_type cell);

/*! \fn cell_type char_to_cell_type(char c)
    \brief Returns the corresponding cell_type out of a character.
    \param c Character to be transformed to cell_type
*/
cell_type char_to_cell_type(char c);

/*! \fn maze read_maze(string filename)
    \brief Reads an object of type maze from txt file
    \param filename text file to be read from
*/
maze read_maze(string filename);

/*! \fn void print_maze(maze m)
    \brief Takes an object of type maze and outputs it to stdout
    \param m maze to be print to stdout
*/
void print_maze(maze m);

/*! \fn pair<algorithm, opt_payload> parse_options(string r_algorithm, string
   r_dist) \brief Takes parsed command line argument into options object \param
   r_algorithm The name of the algorithm \param r_dist The name of the distance
   metric to be used
*/
pair<algorithm, opt_payload> parse_options(string r_algorithm, string r_dist);

/*! \fn void print_path(path p)
    \brief Takes path (vector of points) and prints it to stdout.
   it into an options struct.
   \param p vector of points representing path.
*/
void print_path(path p);

/*! \fn maze paint_maze(const maze &m, path p)
    \brief Embeds a path to a maze.
    \param m Base maze
    \param p Path to be embedded to maze
*/
maze paint_maze(const maze &m, path p);

/*! \fn void save_maze(const maze &m, string filename)
    \brief Embeds a path to a maze.
    \param m Base maze
    \param filename File where maze will be stored.
*/
void save_maze(const maze &m, string filename);

/*! \fn double euclidean(point p1, point p2)
    \brief Computes Euclidean distance between 2 points in 2D space.
    \param p1 Point 1.
    \param p2 Point 2
*/
double euclidean(point p1, point p2);

/*! \fn double manhattan(point p1, point p2)
    \brief Computes Manhattan distance between 2 points in 2D space.
    \param p1 Point 1.
    \param p2 Point 2
*/
double manhattan(point p1, point p2);

path reconstruct_path(map<point, point> came_from, point current);

string pp(point p);

template <typename T>
vector<T> filter(const vector<T> &v, function<bool(const T &)> predicate);

#endif
