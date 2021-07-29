/*
   xtg_pla_reader.cpp

   Copyright (c) 2021 by Daniel Kelley

   Read PLA format

*/

#include <lorina/pla.hpp>
#include <kitty/constructors.hpp>
#include "xtg_pla_reader.hpp"

pla_reader::pla_reader()
{
}

void pla_reader::on_number_of_inputs(std::size_t number_of_inputs) const
{
}

void pla_reader::on_number_of_outputs(std::size_t number_of_outputs) const
{
}

bool pla_reader::on_keyword(const std::string& keyword,
                            const std::string& value) const
{
    return false;
}

void pla_reader::on_end()
{
}

void pla_reader::on_term(const std::string& term, const std::string& out ) const
{
    for ( auto i = 0u; i < term.size(); ++i )
    {
        switch ( term[i] )
        {
        default:
            std::cerr
                << "[w] unknown character '"
                << term[i]
                << "' in PLA input term, treat as don't care\n";
        case '-':
            break;

        case '0':
            break;
        case '1':
            break;
        }
    }

    for ( auto i = 0u; i < out.size(); ++i )
    {
        switch ( out[i] )
        {
        default:
            std::cerr
                << "[w] unknown character '"
                << out[i]
                << "' in PLA output term, treat is 0\n";
        case '0':
            break;

        case '1':
            break;
        }
    }
}
