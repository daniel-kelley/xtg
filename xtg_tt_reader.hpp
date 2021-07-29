/*
   xtg_pla_reader.cpp

   Copyright (c) 2021 by Daniel Kelley

   Read Kitty Truth Table format

*/

#include <kitty/constructors.hpp>

class xtg_tt_reader
{
public:
    xtg_tt_reader(std::string file);
    kitty::dynamic_truth_table &get(std::size_t idx);
    std::size_t length();
private:
    std::vector<kitty::dynamic_truth_table> tt_;
};
