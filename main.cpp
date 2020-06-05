#include "cmdparser.hpp"
#include "maze_generator.hpp"
#include "solver.hpp"
#include "types.hpp"
#include "utils.hpp"
#include <algorithm>
#include <exception>
#include <iostream>
#include <string>

using namespace std;

// algorithm
// metric_distance
// input
// output
// print

void configure_parser(cli::Parser &p)
{
    p.set_required<string>("a", "algorithm", "Pathfinding algorithm.");
    p.set_optional<string>("i", "input", "", "Input file.");
    p.set_optional<string>("o", "output", "", "Output file.");
    p.set_optional<vector<unsigned int>>(
        "g",
        "generate",
        {},
        "Generate maze with {rows}, {cols}, (optional){seed}.");
    p.set_optional<string>("d", "dist", "manhattan", "Distance metric.");
    p.set_optional<bool>("v", "verbose", false, "Prints output to stdout.");
}

int main(int argc, char *argv[])
{
    if (not numeric_limits<double>::has_infinity)
    {
        throw runtime_error(
            "Current floating point representation is not suitable "
            "for this program. IEEE 754 is needed.");
    }
    cli::Parser parser(argc, argv);
    configure_parser(parser);
    parser.run_and_exit_if_error();

    maze m;

    if (parser.get<string>("i") == "" and
        parser.get<vector<unsigned>>("g").empty())
        throw runtime_error(
            "You must specify an input file or maze generator parameters.");
    if (parser.get<string>("i") != "")
    {
        m = read_maze(parser.get<string>("i"));
    }
    else
    {
        vector<unsigned> generator_params = parser.get<vector<unsigned>>("g");
        int              rows, cols;
        unsigned         seed;
        if (generator_params.size() < 2)
            throw runtime_error(
                "You must specify at least the number of rows and columns.");
        else if (generator_params.size() == 2)
        {
            rows = (int)generator_params[0];
            cols = (int)generator_params[1];
            m    = generate_maze(rows, cols);
        }
        else if (generator_params.size() == 3)
        {
            rows = (int)generator_params[0];
            cols = (int)generator_params[1];
            seed = generator_params[2];
            m    = generate_maze(rows, cols, seed);
        }
        else
            throw runtime_error(
                "Unspecified number of arguments for maze generator.");
    }
    print_maze(m);
    auto [pathfinder, opt] =
        parse_options(parser.get<string>("a"), parser.get<string>("d"));
    path p  = pathfinder(m, opt);
    maze mp = paint_maze(m, p);

    if (not parser.get<string>("o").empty())
        save_maze(mp, parser.get<string>("o"));
    if (parser.get<bool>("v"))
        print_maze(mp);

    return 0;
}
