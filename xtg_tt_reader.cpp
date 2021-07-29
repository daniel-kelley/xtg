/*
   xtg_tt_reader.cpp

   Copyright (c) 2021 by Daniel Kelley

*/

#include <cassert>
#include <fstream>
#include <kitty/constructors.hpp>
#include "xtg_tt_reader.hpp"

static bool power_of_two(std::size_t n)
{
    return ((n & (n - 1)) == 0);
}

static size_t ln2(std::size_t n)
{
    std::size_t val = 0;

    while (n >>= 1) {
        val++;
    }

    return val;
}

xtg_tt_reader::xtg_tt_reader(std::string file)
{
    std::ifstream in(file);
    assert(in);
    std::string line;

    while (std::getline(in, line)) {
        std::size_t len = line.length();
        if (len == 0 || line[0] == '#') {
            continue;
        }
        assert(power_of_two(len));
        kitty::dynamic_truth_table tt(ln2(len));
        kitty::create_from_binary_string(tt, line);
        tt_.push_back(tt);
    }
}

kitty::dynamic_truth_table & xtg_tt_reader::get(std::size_t idx)
{
    return tt_[idx];
}

std::size_t xtg_tt_reader::length()
{
    return tt_.size();
}
