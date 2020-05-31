#include "types.hpp"
#include "utils.hpp"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        cout << "A maze txt file must be input as an argument to the program"
             << endl;
        cout << "Usage: ./pathfinder {filename}" << endl;
        return 1;
    }
    else if (argc == 2)
    {
        maze m = read_maze(string(argv[1]));
        print_maze(m);
    }
    else
    {
        cout << "Usage: ./pathfinder {filename}" << endl;
        return 1;
    }

    return 0;
}
