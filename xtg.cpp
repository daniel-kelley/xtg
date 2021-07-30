/*
   xtg.cpp

   Copyright (c) 2021 by Daniel Kelley

   Simple Quantum gate playground.

*/

#include <cassert>
#include <cstdlib>
#include <cstdint>
#include <memory>
#include <iostream>
#include <vector>
#include <algorithm>
#include <easy/esop/constructors.hpp>
#include <kitty/constructors.hpp>
#include <kitty/print.hpp>
#include <boost/optional.hpp>
#include <boost/program_options.hpp>
#include "xtg_tt_reader.hpp"

static int esop(kitty::dynamic_truth_table tt, bool expr)
{
    using synthesizer_t =
        easy::esop::esop_from_tt<kitty::dynamic_truth_table,
                                 easy::sat2::maxsat_rc2,
                                 easy::esop::helliwell_maxsat>;

    easy::esop::helliwell_maxsat_statistics stats;
    easy::esop::helliwell_maxsat_params ps;
    auto const cubes = synthesizer_t( stats, ps ).synthesize(tt);
    if (expr) {
        easy::esop::print_esop_as_exprs(cubes, tt.num_vars());
    } else {
        kitty::print_cubes(cubes);
    }

    return 0;
}

static int xtg(std::string file, bool expr)
{
    int rc = 1;
    xtg_tt_reader rdr(file);
    for ( std::size_t i = 0; i < rdr.length(); ++i ) {
        rc = esop(rdr.get(i), expr);
        if (rc) {
            break;
        }
    }

    return rc;
}

static void usage(std::string prog)
{
    std::cout
        << "usage: "
        << prog
        << " [options] file..."
        << std::endl;
}


int main(int argc, char *argv[])
{
    int rc = 1;
    bool expr = false;

    boost::program_options::options_description
        options("Options");
    options.add_options()
        ("verbose,v", "verbose")
        ("expr,e", "show expression")
        ("help,h", "help");

    boost::program_options::options_description desc;
    desc.add(options);

    boost::program_options::variables_map cli;
    auto parser = boost::program_options::command_line_parser(argc, argv);
    auto args = parser.options(desc).run();
    boost::program_options::store(args, cli);
    boost::program_options::notify(cli);

    if (cli.count("expr")) {
        expr = true;
    }


    if (cli.count("help")) {
        usage(argv[0]);
        std::cout << desc << std::endl;
        rc = 0;
    } else {
        auto v = args.options;
        auto fidx = v.size()-1;
        if (v.size() > 0 && v[fidx].position_key == 0) {
            rc = xtg(v[fidx].value[0], expr);
        } else {
            usage(argv[0]);
            std::cout << desc << std::endl;
            rc = EXIT_FAILURE;
        }
    }

    return rc;
}
