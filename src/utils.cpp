#include "types.hpp"
#include <exception>
#include <fstream>
#include <iostream>

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

    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < cols; ++col)
        {
            try
            {
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
