#ifndef UTILS_HPP
#define UTILS_HPP

#include "types.hpp"
#include "utils.hpp"
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

/*! \fn options read_options(vector<string> argv)
    \brief Takes command line arguments following the input file and transforms
   it into an options struct.
   \param argv The vector of command line arguments
*/
options read_options(vector<string> argv);

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

#endif
