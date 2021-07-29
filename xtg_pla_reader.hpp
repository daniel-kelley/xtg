/*
   xtg_pla_reader.cpp

   Copyright (c) 2021 by Daniel Kelley

   Read PLA format

*/




#include <lorina/pla.hpp>
#include <kitty/constructors.hpp>

class pla_reader : public lorina::pla_reader
{
public:
    pla_reader();
    void on_number_of_inputs(std::size_t number_of_inputs) const override;
    void on_number_of_outputs(std::size_t number_of_outputs) const override;
    bool on_keyword(const std::string& keyword,
                    const std::string& value) const override;
    void on_end();
    void on_term(const std::string& term,
                 const std::string& out ) const override;
private:
    std::vector<kitty::dynamic_truth_table> tt_;
};
