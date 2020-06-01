#include "solver.hpp"
#include "types.hpp"
#include "utils.hpp"
#include <algorithm>
#include <iostream>

using namespace std;

const int NECESSARY_ARGUMENTS = 3;

int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        cout << "A maze txt file must be input as an argument to the program"
             << endl;
        cout << "Usage: ./pathfinder {filename} {algorithm}" << endl;
        return 1;
    }
    else if (argc >= NECESSARY_ARGUMENTS)
    {
        maze           m = read_maze(string(argv[1]));
        vector<string> raw_opts(argc - 2);
        transform(argv + 2, argv + argc, raw_opts.begin(), [](char s[]) {
            return string(s);
        });

        options o = read_options(raw_opts);
        path    p = solve(m, o);
        print_path(p);
        maze mp = paint_maze(m, p);
        save_maze(mp, "res/solved.txt");
        print_maze(mp);
    }
    else
    {
        cout << "Usage: ./pathfinder {filename} {algorithm}" << endl;
        return 1;
    }

    return 0;
}
