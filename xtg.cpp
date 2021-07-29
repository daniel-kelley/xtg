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
#include <fmt/fmt.h>
#include "xtg_pla_reader.hpp"
#include "xtg_tt_reader.hpp"

static int esop(kitty::dynamic_truth_table tt)
{
    using synthesizer_t =
        easy::esop::esop_from_tt<kitty::dynamic_truth_table,
                                 easy::sat2::maxsat_rc2,
                                 easy::esop::helliwell_maxsat>;

    easy::esop::helliwell_maxsat_statistics stats;
    easy::esop::helliwell_maxsat_params ps;
    auto const cubes = synthesizer_t( stats, ps ).synthesize(tt);
    kitty::print_cubes(cubes);
    easy::esop::print_esop_as_exprs(cubes, tt.num_vars());

    return 0;
}

static int xtg(const char *file)
{
    int rc = 1;
    xtg_tt_reader rdr(file);
    for ( auto i = 0; i < rdr.length(); ++i ) {
        rc = esop(rdr.get(i));
        if (rc) {
            break;
        }
    }

    return rc;
}

int main(int argc, char *argv[])
{
    int rc = 1;

    for (int i=1; i<argc; i++) {
        rc = xtg(argv[i]);
        if (rc) {
            break;
        }
    }

    return rc;
}
